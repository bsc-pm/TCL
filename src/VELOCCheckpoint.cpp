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
#include "veloc.h"
#include "mpi.h"
#include "VELOCCheckpoint.hpp"

/********** VELOC CHECKPOINT **********/

VELOCCheckpoint::VELOCCheckpoint(int rank, MPI_Comm comm)
{
    _initialId = 0;
    _restore = false;
    _rank = rank;
    _name_proc = "";

    // Get path of executable file.
    char link[32];
    sprintf(link, "/proc/%d/exe", getpid());
    char path_proc[256];
    int pos = readlink(link, path_proc, sizeof(path_proc));
    if( pos <= 0 )
        assert(0 && "Error getting path of executable file");

    // From the path of executable file, get just the name.
    std::string aux(path_proc, pos); 
    _name_proc.append(aux.substr(aux.find_last_of('/')+1));

    int res;
    char * velocConfig = std::getenv("VELOC_CONF_FILE");
    if(velocConfig == nullptr)
        assert(0 && "There must be a VELOC configuration file provided by the user.");

    // Note: VELOC_Init expects a "char*"
    int initialized = -1;
    MPI_Initialized( &initialized ); 
    assert(initialized && "Trying to initialize VELOC without MPI being initialized.");
    res = VELOC_Init(comm, velocConfig); 
    if(res != VELOC_SUCCESS)
        assert(0 && "Cannot initialize VELOC."); 

    _restart_version = VELOC_Restart_test(_name_proc.c_str(), 0);

    if(_restart_version != VELOC_FAILURE)
        _restore = true;
}

VELOCCheckpoint::~VELOCCheckpoint() {
    // Keep checkpoint files even in successful runs.
    VELOC_Finalize(0);
}

void VELOCCheckpoint::store(CheckpointInfo * checkpointInfo) {
    int res;
    std::vector<CheckpointElement> elements = checkpointInfo->getElements();
    for(unsigned int i = 0; i < checkpointInfo->getNumElements(); i++) {
        size_t copy_size = elements[i].getSize();
        void * copy_address = elements[i].getBaseAddress();
        // Register copies to be stored by VELOC
        res = VELOC_Mem_protect(i, copy_address, 1, copy_size); 
        if(res != VELOC_SUCCESS)
            (*checkpointInfo->_error_handler)(res);
    }

    // VELOC does not provide advise about checkpoint freq, so checkpoint only when mandatory
    if(checkpointInfo->isMandatory()) {
        //! There is no way to specify checkpoint level in VELOC.
        //int level = checkpointInfo->getKind() == CHECKPOINT_DIFF ? checkpointInfo->getLevel() + 4 :  checkpointInfo->getLevel();
        res = VELOC_Checkpoint(_name_proc.c_str(), checkpointInfo->getId()); 
        if(res != VELOC_SUCCESS)
            (*checkpointInfo->_error_handler)(res);
    }
}

void VELOCCheckpoint::load(CheckpointInfo * checkpointInfo) { 
    if(!restore())
        return;

    int res;
    std::vector<CheckpointElement> elements = checkpointInfo->getElements();
    for(unsigned int i = 0; i < checkpointInfo->getNumElements(); i++) {
        size_t copy_size = elements[i].getSize();
        void * copy_address = elements[i].getBaseAddress();
        // Register copies to be stored by VELOC
        res = VELOC_Mem_protect(i, copy_address, 1, copy_size); 
        if(res != VELOC_SUCCESS)
            (*checkpointInfo->_error_handler)(res);
    }

    res = VELOC_Restart(_name_proc.c_str(), _restart_version);
    if(res != VELOC_SUCCESS)
        (*checkpointInfo->_error_handler)(res);
}

/********** VELOC CHECKPOINT **********/
