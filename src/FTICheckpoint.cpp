#include <iostream>
#include <stdlib.h>
#include "fti.h"
#include "mpi.h"
#include "FTICheckpoint.hpp"

/********** FTI CHECKPOINT **********/

FTICheckpoint::FTICheckpoint(int rank, MPI_Comm comm)
{
    _initialId = 0;
    _restore = false;
    _rank = rank;
    _name_proc = "";

    int res;
    char * ftiConfig = std::getenv("FTI_CONF_FILE");
    if(ftiConfig == nullptr)
        assert(0 && "There must be an FTI configuration file provided by the user.");

    // Note: FTI_Init expects a "char*"
    int initialized = -1;
    MPI_Initialized( &initialized ); 
    assert(initialized && "Trying to initialize FTI without MPI being initialized.");
    res = FTI_Init(ftiConfig, comm); 
    if(res != FTI_SCES)
        assert(0 && "Cannot initialize FTI."); 

    if(FTI_Status())
        _restore = true;
}

FTICheckpoint::~FTICheckpoint() {
    FTI_Finalize();
}

void FTICheckpoint::store(CheckpointInfo * checkpointInfo) {
    int res;
    std::vector<CheckpointElement> elements = checkpointInfo->getElements();
    for(unsigned int i = 0; i < checkpointInfo->getNumElements(); i++) {
        size_t copy_size = elements[i].getSize();
        size_t basic_size = CheckpointElement::sizeofBasicDataType(elements[i].getBasicDataType());
        assert(copy_size%basic_size == 0);
        size_t num_basic_elems = copy_size / basic_size;
        void * copy_address = elements[i].getBaseAddress();
        FTIT_type ckptInfo;
        // Initialize the new FTI data type
        res = FTI_InitType(&ckptInfo, basic_size);
        if(res != FTI_SCES)
            (*checkpointInfo->_error_handler)(res);
        // Register copies to be stored by FTI
        res = FTI_Protect(i, copy_address, num_basic_elems, ckptInfo); 
        if(res != FTI_SCES)
            (*checkpointInfo->_error_handler)(res);
    }

    // if checkpoint clause has condition and condition is satisfied, we must do the checkpoint ignoring FTI/SCR advise.
    if(checkpointInfo->isMandatory()) {
        int level = checkpointInfo->getKind() == CHECKPOINT_DIFF ? checkpointInfo->getLevel() + 4 :  checkpointInfo->getLevel();
        res = FTI_Checkpoint(checkpointInfo->getId(), level); 
        if(res != FTI_DONE)
            (*checkpointInfo->_error_handler)(res);
    }
    else{
        assert(checkpointInfo->getKind() == CHECKPOINT_FULL);
        // if checkpoint clause is empty, we trust FTI/SCR to checkpoint when needed.
        res = FTI_Snapshot();
        if(res != FTI_SCES && res != FTI_DONE)
            (*checkpointInfo->_error_handler)(res);
    }
}

void FTICheckpoint::load(CheckpointInfo * checkpointInfo) { 
    if(!restore())
        return;

    int res;
    std::vector<CheckpointElement> elements = checkpointInfo->getElements();
    for(unsigned int i = 0; i < checkpointInfo->getNumElements(); i++) {
        size_t copy_size = elements[i].getSize();
        size_t basic_size = CheckpointElement::sizeofBasicDataType(elements[i].getBasicDataType());
        assert(copy_size%basic_size == 0);
        size_t num_basic_elems = copy_size / basic_size;
        void * copy_address = elements[i].getBaseAddress();
        FTIT_type ckptInfo;
        // Initialize the new FTI data type
        res = FTI_InitType(&ckptInfo, basic_size);
        if(res != FTI_SCES)
            (*checkpointInfo->_error_handler)(res);
        // Register copies to be stored by FTI
        res = FTI_Protect(i, copy_address, num_basic_elems, ckptInfo); 
        if(res != FTI_SCES)
            (*checkpointInfo->_error_handler)(res);
    }

    res = FTI_Recover();
    if(res != FTI_SCES)
        (*checkpointInfo->_error_handler)(res);
}

/********** FTI CHECKPOINT **********/
