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

struct checkpoint_element_t {
    void * _baseAddress;
    size_t _size;

    checkpoint_element_t(void * baseAddress, size_t size) 
        : _baseAddress(baseAddress), _size(size)
    {
    }
};

struct checkpoint_info_t {
    typedef void (*err_handler)(int err_code);
    size_t _numElements;
    checkpoint_element_t *_elements;
    int _level; 
    size_t _id;
    bool _mandatory;
    err_handler error_handler;

    checkpoint_info_t(size_t numElements, checkpoint_element_t * elements, void (*handler)(int)) 
        : _numElements(numElements), _elements(elements)
    {
        error_handler = handler;
    }

    checkpoint_info_t(size_t numElements, checkpoint_element_t * elements, int level, size_t id, bool mandatory, void (*handler)(int)) 
        : _numElements(numElements), _elements(elements), _level(level), _id(id), _mandatory(mandatory)
    {
        error_handler = handler;
    }
};

void checkpoint_library_init(MPI_Comm comm);
void checkpoint_library_shutdown();
void checkpoint_library_load(checkpoint_info_t * checkpointInfo);
void checkpoint_library_store(checkpoint_info_t * checkpointInfo);

#ifdef __cplusplus
}
#endif

#endif /* CHECKPOINT_LIB_BOOTSTRAP_H */
