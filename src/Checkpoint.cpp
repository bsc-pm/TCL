/*
	This file is part of ---- and is licensed under the terms contained in the COPYING file.
	
	Copyright (C) 2018-2019 Barcelona Supercomputing Center (BSC)
*/

#include "Checkpoint.hpp"
#include "FTICheckpoint.hpp"
#include "SCRCheckpoint.hpp"
#include <cstring>
#include <cstdlib>

CheckpointInterface * Checkpoint::_checkpoint;

void Checkpoint::initialize(MPI_Comm comm)
{
    const char * backend_str = std::getenv("CP_BACKEND");
    assert(backend_str != nullptr);
    int rank;
    int res = MPI_Comm_rank(comm, &rank);
    assert(res == MPI_SUCCESS && "Cannot retrieve MPI rank.");
    if(strcmp(backend_str, "FTI") == 0 || strcmp(backend_str, "fti") == 0)
        _checkpoint = (CheckpointInterface *) new FTICheckpoint(rank, comm);
    else if (strcmp(backend_str, "SCR") == 0 || strcmp(backend_str, "scr") == 0)
        _checkpoint = new SCRCheckpoint(rank);
    else
        assert("CP_BACKEND must be either FTI or SCR.");
}

void Checkpoint::shutdown()
{
    delete _checkpoint;
}

void Checkpoint::load(void * checkpointInfo)
{
    _checkpoint->load((CheckpointInfo *)checkpointInfo);
}

void Checkpoint::store(void * checkpointInfo)
{
    _checkpoint->store((CheckpointInfo *)checkpointInfo);
}
