/*
	This file is part of Transparent Checkpoint Lib (TCL) and is licensed under the terms contained in the COPYING file.
	
	Copyright (C) 2018-2019 Barcelona Supercomputing Center (BSC)
*/

#include <tcl.h>
#include "RegisterCPInfo.hpp"
#include "Checkpoint.hpp"

void tcl_register_cpinfo(void *start, basic_data_t data_type, size_t length)
{
    Checkpoint::registerCPInfoElem(start, (cp_basic_data_t) data_type, length);
}
