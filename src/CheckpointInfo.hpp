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
    CHECKPOINT_FULL = 0,
    CHECKPOINT_DIFF = 1,
    // 2, 4, 8, ...
} CheckpointKind;

typedef enum {
      UNKNOWN = 0,
      CHAR,
      SCHAR,
      SHORT,
      INT,
      LONG,
      UCHAR,
      USHORT,
      UINT,
      ULONG,
      FLOAT,
      DOUBLE,
      LDOUBLE,
} cp_basic_data_t;

struct CheckpointElement {
    void * _baseAddress;
    cp_basic_data_t _basicDataType;
    // Total size in BYTES.
    size_t _size;

    CheckpointElement(void * baseAddress, cp_basic_data_t dataType, size_t size) 
        : _baseAddress(baseAddress), _basicDataType(dataType), _size(size)
    {
    }

    inline void * getBaseAddress()
    {
        return _baseAddress;
    }
    
    inline cp_basic_data_t getBasicDataType()
    {
        return _basicDataType;
    }

    inline size_t getSize()
    {
        return _size;
    }

    static size_t sizeofBasicDataType(cp_basic_data_t dataType) 
    {
        switch(dataType) {
            default:
                assert(0 && "Unknown type");
            case UNKNOWN:
                return 1;
            case CHAR:
                return sizeof(char); 
            case SCHAR:
                return sizeof(signed char);
            case SHORT:
                return sizeof(short);
            case INT:
                return sizeof(int);
            case LONG:
                return sizeof(long);
            case UCHAR:
                return sizeof(unsigned char);
            case USHORT:
                return sizeof(unsigned short);
            case UINT:
                return sizeof(unsigned int);
            case ULONG:
                return sizeof(unsigned long);
            case FLOAT:
                return sizeof(float);
            case DOUBLE:
                return sizeof(double);
            case LDOUBLE:
                return sizeof(long double);
        }
        return 0;
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
