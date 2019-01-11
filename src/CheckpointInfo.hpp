/*
	This file is part of ---- and is licensed under the terms contained in the COPYING file.
	
	Copyright (C) 2018-2019 Barcelona Supercomputing Center (BSC)
*/

#ifndef CHECKPOINT_INFO_HPP 
#define CHECKPOINT_INFO_HPP 

#include <cstddef>
#include <cassert>
#include <vector>

typedef enum {
    CHECKPOINT_FULL = (1 << 0),
    CHECKPOINT_DIFF = (1 << 1),
} CheckpointKind;

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
    //CheckpointElement *_elements;
    std::vector<CheckpointElement> _elements;
    int _level; 
    CheckpointKind _kind;
    size_t _id;
    bool _mandatory;
    err_handler _error_handler;

    CheckpointInfo()
        //: _numElements(0), _elements(nullptr), _level(0), _id(0), _mandatory(false), _error_handler(nullptr)
        : _numElements(0), _level(0), _kind(CHECKPOINT_FULL), _id(0), _mandatory(false), _error_handler(nullptr)
    {
    }

    inline void reset()
    {
        _numElements = 0;
        //_elements = nullptr;
        _elements.clear();
        _level = 0;
        _kind = CHECKPOINT_FULL;
        _id = 0;
        _mandatory = false;
        _error_handler = nullptr;
    }

    inline size_t getNumElements()
    {
        return _numElements;
    }

    //inline CheckpointElement * getElements()
    inline std::vector<CheckpointElement> getElements()
    {
        return _elements;
    }

    inline int getLevel()
    {
        return _level;
    }

    inline CheckpointKind getKind()
    {
        return _kind;
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
        return _error_handler;
    }
};

#endif
