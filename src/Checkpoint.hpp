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
public:
    static void initialize(MPI_Comm comm);
    static void shutdown();
    static void load(CheckpointInfo * checkpointInfo);
    static void store(CheckpointInfo * checkpointInfo);
};

#endif
