#ifndef CHECKPOINT_INTERFACE_HPP
#define CHECKPOINT_INTERFACE_HPP 

#include <atomic>
#include <string>
#include "CheckpointInfo.hpp"

// ABSTRACT
class CheckpointInterface {
    protected:
        unsigned long _initialId;
        std::atomic<bool> _restore;
        int _rank;
        std::string _name_proc;

    public:
        virtual ~CheckpointInterface() 
        {}

        virtual void store(CheckpointInfo * checkpointInfo) = 0;
        virtual void load(CheckpointInfo * checkpointInfo) = 0;

        inline bool restore() 
        { 
            return _restore.load(); 
        }

        inline void disableRestore() 
        { 
            bool expected = true;
            __attribute__((unused)) bool exchanged = _restore.compare_exchange_strong(expected, false);
            assert(exchanged);
        }

        inline unsigned long getCheckpointId() 
        { 
            return _initialId; 
        }
};

#endif
