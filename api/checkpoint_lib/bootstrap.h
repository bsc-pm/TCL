/*
	This file is part of ---- and is licensed under the terms contained in the COPYING file.
	
	Copyright (C) 2018-2019 Barcelona Supercomputing Center (BSC)
*/

#ifndef CHECKPOINT_LIB_BOOTSTRAP_H 
#define CHECKPOINT_LIB_BOOTSTRAP_H

#include <cstddef>
#include "mpi.h"

#ifdef __cplusplus
extern "C" {
#endif

void checkpointing_library_init(MPI_Comm comm);

void checkpointing_library_shutdown();

#ifdef __cplusplus
}
#endif

#endif /* CHECKPOINT_LIB_BOOTSTRAP_H */
