/*
	This file is part of Transparent Checkpoint Lib (TCL) and is licensed under the terms contained in the COPYING file.
	
	Copyright (C) 2018-2019 Barcelona Supercomputing Center (BSC)
*/

#ifndef MULTIDIMENSIONAL_REGISTER_HPP
#define MULTIDIMENSIONAL_REGISTER_HPP


#include <tcl/multidimensional-register.h>
#include "RegisterCPInfo.hpp"
#include "MultidimensionalRegisterTraversal.hpp"

#ifdef NDEBUG
#define _AI_ inline __attribute((always_inline))
#else
#define _AI_ inline
#endif

#define _UU_ __attribute__((unused))

_AI_ void register_cpinfo_base(
	void *baseAddress,
	long currentDimSize, long currentDimStart, long currentDimEnd
);

/*template<>*/
_AI_ void register_cpinfo_base(
	void *baseAddress,
	_UU_ long currentDimSize, long currentDimStart, long currentDimEnd
) {
	size_t start = (size_t) baseAddress;
	start += currentDimStart;
	tcl_register_cpinfo((void *) start, currentDimEnd - currentDimStart);
}

template <typename... TS>
static _AI_ void register_cpinfo_skip_next(
	void *baseAddress,
	long currentDimSize, long currentDimStart, long currentDimEnd,
	long nextDimSize, long nextDimStart, long nextDimEnd,
	TS... otherDimensions
);


static _AI_ void register_cpinfo(
	void *baseAddress,
	long currentDimSize, long currentDimStart, long currentDimEnd
) {
	register_cpinfo_base(baseAddress, currentDimSize, currentDimStart, currentDimEnd);
}

template <typename... TS>
static _AI_ void register_cpinfo(
	void *baseAddress,
	long currentDimSize, long currentDimStart, long currentDimEnd,
	TS... otherDimensions
) {
	if (currentDimensionIsContinuous(otherDimensions...)) {
		register_cpinfo_skip_next(baseAddress,
			currentDimSize * getCurrentDimensionSize(otherDimensions...),
			currentDimStart * getCurrentDimensionSize(otherDimensions...),
			currentDimEnd * getCurrentDimensionSize(otherDimensions...),
			otherDimensions...
		);
	} else {
		size_t stride = getStride<>(otherDimensions...);
		char *currentBaseAddress = (char *) baseAddress;
		currentBaseAddress += currentDimStart * stride;
		
		for (long index = currentDimStart; index < currentDimEnd; index++) {
			register_cpinfo(currentBaseAddress, otherDimensions...);
			currentBaseAddress += stride;
		}
	}
}


template <typename... TS>
static _AI_ void register_cpinfo_skip_next(
	void *baseAddress,
	long currentDimSize, long currentDimStart, long currentDimEnd,
	_UU_ long nextDimSize, _UU_ long nextDimStart, _UU_ long nextDimEnd,
	TS... otherDimensions
) {
	register_cpinfo(baseAddress, currentDimSize, currentDimStart, currentDimEnd, otherDimensions...);
}

#undef _AI_
#undef _UU_


#endif // MULTIDIMENSIONAL_REGISTER_HPP
