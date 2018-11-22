/*
	This file is part of Transparent Checkpoint Lib (TCL) and is licensed under the terms contained in the COPYING file.
	
	Copyright (C) 2018-2019 Barcelona Supercomputing Center (BSC)
*/

#ifndef MULTIDIMENSIONAL_REGISTER_TRAVERSAL_HPP
#define MULTIDIMENSIONAL_REGISTER_TRAVERSAL_HPP


#include <cstddef>


#ifdef NDEBUG
#define _AI_ inline __attribute((always_inline))
#else
#define _AI_ inline
#endif

#define _UU_ __attribute__((unused))


template <typename... TS>
static _AI_ bool currentDimensionIsContinuous(long currentDimSize, long currentDimStart, long currentDimEnd, _UU_ TS... otherDimensions)
{
	return (currentDimStart == 0) && (currentDimEnd == currentDimSize);
}


template <typename... TS>
static _AI_ long getCurrentDimensionSize(long currentDimSize, _UU_ long currentDimStart, _UU_ long currentDimEnd, _UU_ TS... otherDimensions)
{
	return currentDimSize;
}

template <typename... TS>
static _AI_ long getCurrentDimensionStart(_UU_ long currentDimSize, long currentDimStart, _UU_ long currentDimEnd, _UU_ TS... otherDimensions)
{
	return currentDimStart;
}

template <typename... TS>
static _AI_ long getCurrentDimensionEnd(_UU_ long currentDimSize, _UU_ long currentDimStart, long currentDimEnd, _UU_ TS... otherDimensions)
{
	return currentDimEnd;
}


template <typename... TS>
static _AI_ size_t getStride()
{
	return 1;
}

template <typename... TS>
static _AI_ size_t getStride(long currentDimSize, _UU_ long currentDimStart, _UU_ long currentDimEnd, TS... otherDimensions)
{
	return currentDimSize * getStride<>(otherDimensions...);
}


template <typename... TS>
static _AI_ size_t getStartOffset()
{
	return 0;
}

template <typename... TS>
static _AI_ size_t getStartOffset(_UU_ long currentDimSize, long currentDimStart, _UU_ long currentDimEnd, TS... otherDimensions)
{
	return currentDimStart * getStride<>(otherDimensions...) + getStartOffset<>(otherDimensions...);
}


template <typename... TS>
static _AI_ size_t getDiscreteSize()
{
	return 1;
}

template <typename... TS>
static _AI_ size_t getDiscreteSize(_UU_ long currentDimSize, long currentDimStart, long currentDimEnd, TS... otherDimensions)
{
	return (currentDimEnd - currentDimStart) * getDiscreteSize<>(otherDimensions...);
}


#undef _AI_
#undef _UU_


#endif // MULTIDIMENSIONAL_REGISTER_TRAVERSAL_HPP
