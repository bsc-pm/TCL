#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <dlfcn.h>
#include "scr.h"
#include "mpi.h"
#include "SCRCheckpoint.hpp"
/********** SCR CHECKPOINT **********/

SCRCheckpoint::SCRCheckpoint(int rank)
{
    _initialId = 0;
    _restore = false;
    _rank = rank;
    _name_proc = "";

    int initialized = -1;
    MPI_Initialized(&initialized); 
    assert(initialized && "Trying to initialize SCR without MPI being initialized.");
    int res = SCR_Init();
    if(res != SCR_SUCCESS)
        assert(0 && "Cannot initialize SCR."); 

    // Get path of executable file.
    char link[32];
    sprintf(link, "/proc/%d/exe", getpid());
    char path_proc[256];
    int pos = readlink(link, path_proc, sizeof(path_proc));
    if( pos <= 0 )
        assert(0 && "Error getting path of executable file");

    // From the path of executable file, get just the name.
    std::string aux(path_proc, pos); 
    _name_proc.append(aux.substr(aux.find_last_of('/')));


    char name[256];
    sprintf(name, "%s-%d.ckpt", _name_proc.c_str(), _rank);
    /* get backup file path */
    char path[SCR_MAX_FILENAME];
    int found_cp = 0;
    int status = 0;
    if (SCR_Route_file(name, path) == SCR_SUCCESS) {
        int fd = open (path, O_RDWR | O_CREAT, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP | S_IWOTH);
        if(fd < 0) 
            perror("ERROR: ");
        assert(fd >= 0 && "Cannot open checkpoint");

        int num_read = read(fd, &_initialId, sizeof(unsigned long));
        assert(close(fd) == 0 && "Error closing checkpoint file.");

        if(num_read != sizeof(unsigned long))
            status = -1;
        else
            found_cp = 1;
    }

    /* determine whether all tasks successfully read their checkpoint file */
    int all_found_checkpoint = 0;
    MPI_Allreduce(&found_cp, &all_found_checkpoint, 1, MPI_INT, MPI_LAND, MPI_COMM_WORLD);
    if(!all_found_checkpoint)
        status = -2;

    /* check that everyone is at the same timestep */
    int sendval = _initialId;
    int timestep_and, timestep_or;
    MPI_Allreduce(&sendval, &timestep_and, 1, MPI_INT, MPI_BAND, MPI_COMM_WORLD);
    MPI_Allreduce(&sendval, &timestep_or, 1, MPI_INT, MPI_BOR, MPI_COMM_WORLD);
    if(timestep_and != timestep_or)
        status = -3;
    if(status == 0)
        _restore = true;
}

SCRCheckpoint::~SCRCheckpoint() {
    SCR_Finalize();
}

void SCRCheckpoint::store(CheckpointInfo * checkpointInfo) {
    unsigned int saved_data = 0;
    int perform_checkpoint = 0;
    int res;

    // if checkpoint clause has condition and the condition is satisfied, we must do the checkpoint ignoring FTI/SCR advise.
    if(checkpointInfo->isMandatory())
        perform_checkpoint = 1;
    else {
        res = SCR_Need_checkpoint(&perform_checkpoint);
        if(res != SCR_SUCCESS)
            (*checkpointInfo->_error_handler)(res);
    }

    if(perform_checkpoint) {
        res = SCR_Start_checkpoint();
        if(res != SCR_SUCCESS)
            (*checkpointInfo->_error_handler)(res);
        // Get backup file path
        char name[256];
        sprintf(name, "%s-%d.ckpt", _name_proc.c_str(), _rank);
        char path[SCR_MAX_FILENAME];
        unsigned int cp_size_prov = 0;
        if(SCR_Route_file(name, path)==SCR_SUCCESS){
            int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP | S_IWOTH);
            if(fd < 0) 
                perror("ERROR: ");
            assert(fd >= 0 && "Cannot open checkpoint."); 

            /* Save checkpoint id */
            unsigned long writeval = _initialId+checkpointInfo->getId();
            saved_data = write(fd, &writeval, sizeof(unsigned long));

            /* Save data */
            std::vector<CheckpointElement> elements = checkpointInfo->getElements();
            for(unsigned int i = 0; i < checkpointInfo->getNumElements(); i++) {
                size_t copy_size = elements[i].getSize();
                void * copy_address = elements[i].getBaseAddress();
                saved_data += write(fd, copy_address, copy_size);
                cp_size_prov += copy_size;
            }

            assert(close(fd) == 0 && "Error closing checkpoint file.");
        }
        int is_valid = (saved_data == (cp_size_prov+sizeof(unsigned long)));
        res = SCR_Complete_checkpoint(is_valid);
        if( !is_valid || res != SCR_SUCCESS )
            (*checkpointInfo->_error_handler)(res);
            
    }
}

void SCRCheckpoint::load(CheckpointInfo * checkpointInfo) {
    if(!restore())
        return;

    char name[256];
    sprintf(name, "%s-%d.ckpt", _name_proc.c_str(), _rank);
    /* get backup file path */
    char path[SCR_MAX_FILENAME];
    int found_cp = 0;
    int status = 0;
    void * tmp = NULL;
    size_t copies_size = sizeof(unsigned long);
    std::vector<CheckpointElement> elements = checkpointInfo->getElements();
    for(unsigned int i = 0; i < checkpointInfo->getNumElements(); i++) {
        size_t copy_size = elements[i].getSize();
        copies_size += copy_size;
    }

    if(SCR_Route_file(name, path) == SCR_SUCCESS) {
        int fd = open(path, O_RDWR | O_CREAT, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP | S_IWOTH);
        if(fd < 0) 
            perror( "ERROR: " );
        assert(fd >= 0 && "Cannot open checkpoint."); 

        tmp = (void *) mmap(NULL, copies_size, PROT_WRITE|PROT_READ, MAP_SHARED, fd, 0);
        assert(close(fd) == 0 && "Error closing checkpoint file.");

        if(tmp == MAP_FAILED)
            status = -1;
        else
            found_cp = 1;
    }

    /* determine whether all tasks successfully read their checkpoint file */
    int all_found_checkpoint = 0;
    MPI_Allreduce(&found_cp, &all_found_checkpoint, 1, MPI_INT, MPI_LAND, MPI_COMM_WORLD);
    if(!all_found_checkpoint)
        status = -2;

    if(status == 0) {
        //! Ignore checkpoint id.
        char * aux = (char *) tmp + sizeof(unsigned long);
        size_t copies_size2 = 0;
        for(unsigned int i = 0; i < checkpointInfo->getNumElements(); i++) {
            size_t copy_size = elements[i].getSize();
            void * copy_address = elements[i].getBaseAddress();
            memcpy(copy_address, aux, copy_size);
            aux += copy_size;
            copies_size2 += copy_size;
        }
        assert(copies_size-sizeof(unsigned long) == copies_size2 && "Error restoring checkpoint.");
        munmap(tmp, copies_size);
    }
    else {
        (*checkpointInfo->_error_handler)(status);
    }
}

/********** SCR CHECKPOINT **********/
