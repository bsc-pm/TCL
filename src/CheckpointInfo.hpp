/*
	This file is part of ---- and is licensed under the terms contained in the COPYING file.
	
	Copyright (C) 2018-2019 Barcelona Supercomputing Center (BSC)
*/

#ifndef CHECKPOINT_INFO_HPP 
#define CHECKPOINT_INFO_HPP 

#include <cstddef>
#include <cassert>

struct CheckpointElement {
    void * _baseAddress;
    size_t _size;

    CheckpointElement(void * baseAddress, size_t size) 
        : _baseAddress(baseAddress), _size(size)
    {
    }

    inline void * getBaseAddress()
    {
        return _baseAddress;
    }

    inline size_t getSize()
    {
        return _size;
    }
};

struct CheckpointInfo {
    typedef void (*err_handler)(int err_code);
    size_t _numElements;
    CheckpointElement *_elements;
    int _level; 
    size_t _id;
    bool _mandatory;
    err_handler error_handler;

    CheckpointInfo(size_t numElements, CheckpointElement * elements, void (*handler)(int)) 
        : _numElements(numElements), _elements(elements)
    {
        error_handler = handler;
    }

    CheckpointInfo(size_t numElements, CheckpointElement * elements, int level, size_t id, bool mandatory, void (*handler)(int)) 
        : _numElements(numElements), _elements(elements), _level(level), _id(id), _mandatory(mandatory)
    {
        error_handler = handler;
    }

    inline size_t getNumElements()
    {
        return _numElements;
    }

    inline CheckpointElement * getElements()
    {
        return _elements;
    }

    inline int getLevel()
    {
        return _level;
    }

    inline size_t getId()
    {
        return _id;
    }

    inline bool isMandatory() 
    {
        return _mandatory;
    }

    err_handler getErrorHandler() 
    {
        return error_handler;
    }
};

#endif
