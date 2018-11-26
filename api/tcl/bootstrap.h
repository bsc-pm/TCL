/*
	This file is part of ---- and is licensed under the terms contained in the COPYING file.
	
	Copyright (C) 2018-2019 Barcelona Supercomputing Center (BSC)
*/

#ifndef TCL_BOOTSTRAP_H 
#define TCL_BOOTSTRAP_H

#include <stddef.h>
#include <stdbool.h>
#include "mpi.h"

#pragma GCC visibility push(default)

#ifdef __cplusplus
extern "C" {
#endif

void tcl_init(MPI_Comm comm);
void tcl_shutdown(void);
void tcl_begin_load(void (*error_handler)(int));
void tcl_end_load(void);
void tcl_begin_store(int level, size_t id, bool mandatory, void (*error_handler)(int));
void tcl_end_store(void);

#ifdef __cplusplus
}
#endif

#endif /* TCL_BOOTSTRAP_H */
