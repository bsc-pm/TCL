#!/bin/sh

#	This file is part of Transparent Checkpoint Lib (TCL) and is licensed under the terms contained in the COPYING file.
#	
#	Copyright (C) 2018-2019 Barcelona Supercomputing Center (BSC)


if [ $# -lt 1 ] ; then
	echo Usage: $0 '<max dimensions>' 1>&2
	exit 1
fi


maxdimensions=$1
shift


. $(dirname $0)/common.sh


echo '#include <tcl/multidimensional-register.h>'
echo ''
echo '#include "MultidimensionalRegister.hpp"'
echo ''
echo ''
echo '#pragma GCC visibility push(default)'
echo ''
echo ''



registration_function="register_cpinfo"
	
for dimensions in $(seq 1 ${maxdimensions}) ; do
	generate_register_named_prototype ${dimensions} "tcl_register_cpinfo${dimensions}"
	echo " {"
	echo "	${registration_function}("
	
	echo "		base_address,"
	
	for level in $(seq ${dimensions} -1 1) ; do
		if [ "${level}" -ne 1 ] ; then
			opt_comma=","
		else
			opt_comma=""
		fi
		
		echo "		dim${level}size, dim${level}start, dim${level}end${opt_comma}"
	done
	echo "	);"
	
	echo "}"
	echo
done

echo ''
echo ''
echo '#pragma GCC visibility pop'
