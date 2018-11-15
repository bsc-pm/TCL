/*
	This file is part of ---- and is licensed under the terms contained in the COPYING file.
	
	Copyright (C) 2018-2019 Barcelona Supercomputing Center (BSC)
*/

#include <checkpoint_lib.h>
#include "Checkpoint.hpp"

void checkpointing_library_init(MPI_Comm comm);

void checkpointing_library_shutdown();

void checkpointing_library_init(MPI_Comm comm)
{
    Checkpoint::initialize(comm);
}

void checkpointing_library_shutdown()
{
    Checkpoint::shutdown();
}
