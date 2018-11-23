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

echo '/*'
echo '	This file is part of Transparent Checkpoint Lib (TCL) and is licensed under the terms contained in the COPYING file.'
echo '	'
echo '	Copyright (C) 2018-2019 Barcelona Supercomputing Center (BSC)'
echo '*/'
echo
echo
echo '#ifndef TCL_MULTIDIMENSIONAL_REGISTER_H'
echo '#define TCL_MULTIDIMENSIONAL_REGISTER_H'
echo
echo '#pragma GCC visibility push(default)'
echo
echo
echo 'enum tcl_multidimensional_register_api_t { tcl_multidimensional_register_api = 5 };'
echo
echo
echo "#ifndef TCL_MAX_REGISTER_DIMENSIONS"
echo "#define TCL_MAX_REGISTER_DIMENSIONS ${maxdimensions}"
echo "#endif"
echo
echo
echo "#ifdef __cplusplus"
echo "extern \"C\" {"
echo "#endif"
echo
echo
echo "enum {"
echo "\t\t__tcl_max_dimensions = 8"
echo "};"
echo
echo


for dimensions in $(seq 1 ${maxdimensions}) ; do
	generate_register_full_prototype ${dimensions} ${type}
	echo ";"
	echo
done

echo
echo "#ifdef __cplusplus"
echo "}"
echo "#endif"
echo
echo
echo '#endif /* TCL_MULTIDIMENSIONAL_REGISTER_H */'

