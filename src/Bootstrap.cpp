/*
	This file is part of ---- and is licensed under the terms contained in the COPYING file.
	
	Copyright (C) 2018-2019 Barcelona Supercomputing Center (BSC)
*/

#include <tcl.h>
#include "Checkpoint.hpp"

void tcl_init(MPI_Comm comm)
{
    Checkpoint::initialize(comm);
}

void tcl_shutdown()
{
    Checkpoint::shutdown();
}

void tcl_begin_load(void (*error_handler)(int))
{
    Checkpoint::beginLoad(error_handler);
}

void tcl_end_load() 
{
    Checkpoint::endLoad();
}

void tcl_begin_store(int level, size_t id, bool mandatory, void (*error_handler)(int))
{
    Checkpoint::beginStore(level, id, mandatory, error_handler);
}

void tcl_end_store()
{
    Checkpoint::endStore();
}
