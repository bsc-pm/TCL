#	This file is part of Transparent Checkpoint Lib (TCL) and is licensed under the terms contained in the COPYING file.
#	
#	Copyright (C) 2018-2019 Barcelona Supercomputing Center (BSC)


generate_register_full_prototype() {
	local dimensions=$1
	local type=$2
	local commaatend
	
	/bin/echo '/** \brief Register data on a '${dimensions}'-dimensional region of addresses to be checkpointed */'
	/bin/echo 'void tcl_register_cpinfo'${dimensions}'('
	
	/bin/echo '	void *base_address,'
	/bin/echo '	/* First is the continuous dimension in bytes, the rest are based on the previous dimension */'
	/bin/echo '	/* dimXstart is the first index/byte and dimXend is the next byte/index outside of the region */'
	for currentdimension in $(seq 1 ${dimensions}) ; do
		if [ ${currentdimension} -eq ${dimensions} ] ; then
			commaatend=""
		else
			commaatend=","
		fi
		
		/bin/echo "	long dim${currentdimension}size, long dim${currentdimension}start, long dim${currentdimension}end${commaatend}"
	done
	/bin/echo -n ')'
}

generate_register_named_prototype() {
    local dimensions=$1
    local name=$2
    local indentation=$3
    local commaatend

    if [ "${indentation}" != "" ] ; then
        indentation=$(emit_tabs ${indentation})
    fi

    /bin/echo "void ${name}("

    /bin/echo "${indentation}   void *base_address,"
    /bin/echo "${indentation}   /* First is the continuous dimension in bytes, the rest are based on the previous dimension */"
    /bin/echo "${indentation}   /* dimXstart is the first index/byte and dimXend is the next byte/index outside of the region */"
    for currentdimension in $(seq 1 ${dimensions}) ; do
        if [ ${currentdimension} -eq ${dimensions} ] ; then
            commaatend=""
        else
            commaatend=","
        fi

        /bin/echo "${indentation}   long dim${currentdimension}size, long dim${currentdimension}start, long dim${currentdimension}end${commaatend}"
    done
    /bin/echo -n "${indentation})"
}

