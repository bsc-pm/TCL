/*
	This file is part of ---- and is licensed under the terms contained in the COPYING file.
	
	Copyright (C) 2018-2019 Barcelona Supercomputing Center (BSC)
*/

#include "Checkpoint.hpp"
#include <cstring>
#include <cstdlib>

#ifdef FTI_BACKEND
#include "FTICheckpoint.hpp"
#endif

#ifdef SCR_BACKEND
#include "SCRCheckpoint.hpp"
#endif

CheckpointInterface * Checkpoint::_checkpoint;
CheckpointInfo Checkpoint::_currentCheckpointInfo;
bool Checkpoint::_operationInProcess;

void Checkpoint::initialize(MPI_Comm comm)
{
    const char * backend_str = std::getenv("TCL_BACKEND");
    assert(backend_str != nullptr);
    int rank;
    int res = MPI_Comm_rank(comm, &rank);
    assert(res == MPI_SUCCESS && "Cannot retrieve MPI rank.");

    if(strcmp(backend_str, "FTI") == 0 || strcmp(backend_str, "fti") == 0)
#ifdef FTI_BACKEND
        _checkpoint = (CheckpointInterface *) new FTICheckpoint(rank, comm);
#else
        assert(0 && "Trying to use FTI as backend but FTI is not configured.");
#endif
    else if (strcmp(backend_str, "SCR") == 0 || strcmp(backend_str, "scr") == 0)
#ifdef SCR_BACKEND
        _checkpoint = new SCRCheckpoint(rank);
#else
        assert(0 && "Trying to use SCR as backend but SCR is not configured.");
#endif
    else
        assert(0 && "TCL_BACKEND must be either FTI or SCR.");


    _operationInProcess = false;
}

void Checkpoint::shutdown()
{
    assert(!_operationInProcess);
    delete _checkpoint;
}

void Checkpoint::beginLoad(void (*error_handler)(int))
{
    _operationInProcess = true;
    _currentCheckpointInfo._error_handler = error_handler;
}

void Checkpoint::endLoad()
{
    assert(_operationInProcess);
    _checkpoint->load(&_currentCheckpointInfo);
    _checkpoint->disableRestore();
    _currentCheckpointInfo.reset();
    _operationInProcess = false;
}

void Checkpoint::beginStore(int level, size_t id, bool mandatory, void (*error_handler)(int))
{
    _operationInProcess = true;
    _currentCheckpointInfo._level = level;
    _currentCheckpointInfo._id = id;
    _currentCheckpointInfo._mandatory = mandatory;
    _currentCheckpointInfo._error_handler = error_handler;
}

void Checkpoint::endStore()
{
    assert(_operationInProcess);
    _checkpoint->store(&_currentCheckpointInfo);
    _currentCheckpointInfo.reset();
    _operationInProcess = false;
}

void Checkpoint::registerCPInfoElem(void *baseAddress, size_t size)
{
    assert(_operationInProcess);
    _currentCheckpointInfo._numElements++;
    _currentCheckpointInfo._elements.push_back(CheckpointElement(baseAddress,size));
}
