#ifndef FTI_CHECKPOINT_HPP 
#define FTI_CHECKPOINT_HPP 

#include "CheckpointInterface.hpp"

class FTICheckpoint: public CheckpointInterface {
    public:
    FTICheckpoint(int rank, MPI_Comm comm);
    ~FTICheckpoint();

    void store(CheckpointInfo * checkpointInfo);
    void load(CheckpointInfo * checkpointInfo);
};
#endif /* FTI_CHECKPOINT_HPP */
