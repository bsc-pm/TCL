/*
	This file is part of ---- and is licensed under the terms contained in the COPYING file.
	
	Copyright (C) 2018-2019 Barcelona Supercomputing Center (BSC)
*/

#ifndef CHECKPOINT_HPP 
#define CHECKPOINT_HPP 

#include "CheckpointInfo.hpp"
#include "CheckpointInterface.hpp"
#include "mpi.h"

class Checkpoint {
    static CheckpointInterface *_checkpoint;
    static CheckpointInfo _currentCheckpointInfo;
    static bool _operationInProcess;
public:
    static void initialize(MPI_Comm comm);
    static void shutdown();
    static void beginLoad(void (*error_handler)(int));
    static void endLoad();
    static void beginStore(int level, CheckpointKind kind, size_t id, bool mandatory, void (*error_handler)(int));
    static void endStore();
    static void registerCPInfoElem(void *baseAddress, cp_basic_data_t data_type, size_t size);
};

#endif
