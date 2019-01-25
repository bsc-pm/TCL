#ifndef VELOC_CHECKPOINT_HPP 
#define VELOC_CHECKPOINT_HPP 

#include "CheckpointInterface.hpp"

class VELOCCheckpoint: public CheckpointInterface {
    int _restart_version;

    public:
    VELOCCheckpoint(int rank, MPI_Comm comm);
    ~VELOCCheckpoint();

    void store(CheckpointInfo * checkpointInfo);
    void load(CheckpointInfo * checkpointInfo);
};
#endif /* VELOC_CHECKPOINT_HPP */
