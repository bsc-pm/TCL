#ifndef SCR_CHECKPOINT_HPP
#define SCR_CHECKPOINT_HPP

#include "CheckpointInterface.hpp"

class SCRCheckpoint: public CheckpointInterface {

    public:
        SCRCheckpoint(int rank);
        ~SCRCheckpoint();

        void store(CheckpointInfo * checkpointInfo);
        void load(CheckpointInfo * checkpointInfo);
};

#endif /* SCR_CHECKPOINT_HPP */
