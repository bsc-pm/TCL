/*
	This file is part of ---- and is licensed under the terms contained in the COPYING file.
	
	Copyright (C) 2018-2019 Barcelona Supercomputing Center (BSC)
*/

#include "Checkpoint.hpp"
#include "FTICheckpoint.hpp"
#include "SCRCheckpoint.hpp"
#include <cstring>
#include <cstdlib>

void Checkpoint::initialize(MPI_Comm comm)
{
    const char * backend_str = std::getenv("CP_BACKEND");
    if(strcmp(backend_str, "FTI"))
        _checkpoint = (CheckpointInterface *) new FTICheckpoint(0, comm);
    else if (strcmp(backend_str, "SCR"))
        _checkpoint = new SCRCheckpoint(0);
    else
        assert("CP_BACKEND must be either FTI or SCR.");
}

void Checkpoint::shutdown()
{
    delete _checkpoint;
}

void Checkpoint::load(CheckpointInfo * checkpointInfo)
{
    _checkpoint->load(checkpointInfo);
}

void Checkpoint::store(CheckpointInfo * checkpointInfo)
{
    _checkpoint->store(checkpointInfo);
}
