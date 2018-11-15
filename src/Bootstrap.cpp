/*
	This file is part of ---- and is licensed under the terms contained in the COPYING file.
	
	Copyright (C) 2018-2019 Barcelona Supercomputing Center (BSC)
*/

#include <checkpoint_lib.h>
#include "Checkpoint.hpp"

void checkpoint_library_init(MPI_Comm comm)
{
    Checkpoint::initialize(comm);
}

void checkpoint_library_shutdown()
{
    Checkpoint::shutdown();
}

void checkpoint_library_load(checkpoint_info_t * checkpointInfo) 
{
    Checkpoint::load((void *)checkpointInfo);
}

void checkpoint_library_store(checkpoint_info_t * checkpointInfo) 
{
    Checkpoint::store((void *)checkpointInfo);
}
