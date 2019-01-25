#	This file is part of Transparent Checkpoint Lib (TCL) and is licensed under the terms contained in the COPYING file.
#	
#	Copyright (C) 2018-2019 Barcelona Supercomputing Center (BSC)

ACLOCAL_AMFLAGS=-I m4


END=

tclincludedir = $(includedir)/tcl

tclinclude_HEADERS = \
	api/tcl/bootstrap.h \
	$(END)

include_HEADERS = \
	api/tcl.h \
	$(END)

nodist_tclinclude_HEADERS = \
	tcl/multidimensional-register.h 

noinst_HEADERS = \
	src/Checkpoint.hpp \
	src/CheckpointInfo.hpp \
	src/CheckpointInterface.hpp \
	src/FTICheckpoint.hpp \
	src/MultidimensionalRegister.hpp \
	src/MultidimensionalRegisterTraversal.hpp \
	src/RegisterCPInfo.hpp \
	src/SCRCheckpoint.hpp \
	src/VELOCCheckpoint.hpp

tcl_generated_headers = \
	tcl/multidimensional-register.h 

CLEANFILES = $(tcl_generated_headers)

BUILT_SOURCES = \
	$(tcl_generated_headers)
#
# Automatically generated API headers
#
EXTRA_DIST = \
	scripts/common.sh \
	scripts/generate_multidim_functions.sh \
	scripts/generate_multidimensional_register_prototypes.sh

common_includes=\
 -I$(top_builddir)\
 -I$(top_srcdir)/src/\
 $(END)

api_includes=\
 -I$(top_srcdir)/api/\
 $(END)

nodist_common_sources = \
	$(tcl_generated_headers)

common_sources=\
    src/Bootstrap.cpp \
    src/Checkpoint.cpp \
    src/RegisterCPInfo.cpp \
	$(END)

fti_sources = \
    src/FTICheckpoint.hpp \
    src/FTICheckpoint.cpp \
    $(END)

scr_sources = \
    src/SCRCheckpoint.hpp \
    src/SCRCheckpoint.cpp \
    $(END)

veloc_sources = \
    src/VELOCCheckpoint.hpp \
    src/VELOCCheckpoint.cpp \
    $(END)

MAX_REGION_DIMENSIONS = 8
AM_V_GEN = $(am__v_GEN_@AM_V@)

tcl/multidimensional-register.h: $(top_srcdir)/scripts/common.sh $(top_srcdir)/scripts/generate_multidimensional_register_prototypes.sh
	$(AM_V_GEN)mkdir -p tcl ; \
	$(top_srcdir)/scripts/generate_multidimensional_register_prototypes.sh $(MAX_REGION_DIMENSIONS) > $@

MultidimensionalRegister.cpp: $(top_srcdir)/scripts/common.sh $(top_srcdir)/scripts/generate_multidim_functions.sh
	$(AM_V_GEN)$(top_srcdir)/scripts/generate_multidim_functions.sh $(MAX_REGION_DIMENSIONS) > $@

multidimensional_sources = MultidimensionalRegister.cpp

nodist_common_sources += \
	$(multidimensional_sources)
BUILT_SOURCES += \
	$(multidimensional_sources)
CLEANFILES += \
	$(multidimensional_sources)

AM_CPPFLAGS=@cc_dep_CPPFLAGS@ @mpiinc@ @ftiinc@ @scrinc@ @velocinc@ $(common_includes) $(api_includes) -DLIBDIR='$(libdir)'
AM_CXXFLAGS=@cc_dep_CXXFLAGS@
AM_LDFLAGS=@mpilib@ @ftilib@ @scrlib@ @veloclib@
LIBS+=@mpilibs@ @ftilibs@ @scrlibs@ @veloclibs@

common_performance_CPPFLAGS= $(AM_CPPFLAGS) @performance_CPPFLAGS@
common_debug_CPPFLAGS= $(AM_CPPFLAGS) @debug_CPPFLAGS@
common_performance_CXXFLAGS= $(AM_CXXFLAGS) @performance_CXXFLAGS@
common_debug_CXXFLAGS= $(AM_CXXFLAGS) @debug_CXXFLAGS@

debug_LTLIBRARIES=
performance_LTLIBRARIES=

noinst_LTLIBRARIES=

if is_debug_enabled
debug_LTLIBRARIES+=debug/libtcl.la
debug_libtcl_la_LIBADD=$(common_libadd)
debug_libtcl_la_DEPENDENCIES=$(common_libadd) @tcl_config_libs_debug@

if FTI_SUPPORT
common_debug_CPPFLAGS+=-DFTI_BACKEND
common_debug_CXXFLAGS+=-DFTI_BACKEND
noinst_LTLIBRARIES+= debug/libtclfti.la
debug_libtclfti_la_CPPFLAGS=$(common_includes) $(common_debug_CPPFLAGS) @mpiinc@ @ftiinc@
debug_libtclfti_la_CXXFLAGS=$(common_includes) $(common_debug_CXXFLAGS)
debug_libtclfti_la_LDFLAGS=$(AM_LDFLAGS) @ftilib@ 
debug_libtclfti_la_LIBADD=@ftilibs@
debug_libtclfti_la_SOURCES=$(fti_sources)
debug_libtcl_la_LIBADD+=debug/libtclfti.la
debug_libtcl_la_DEPENDENCIES+=debug/libtclfti.la
endif

if SCR_SUPPORT
common_debug_CPPFLAGS+=-DSCR_BACKEND
common_debug_CXXFLAGS+=-DSCR_BACKEND
noinst_LTLIBRARIES+= debug/libtclscr.la
debug_libtclscr_la_CPPFLAGS=$(common_includes) $(common_debug_CPPFLAGS) @mpiinc@ @scrinc@
debug_libtclscr_la_CXXFLAGS=$(common_includes) $(common_debug_CXXFLAGS)
debug_libtclscr_la_LDFLAGS=$(AM_LDFLAGS) @scrlib@ 
debug_libtclscr_la_LIBADD=@scrlibs@
debug_libtclscr_la_SOURCES=$(scr_sources)
debug_libtcl_la_LIBADD+=debug/libtclscr.la
debug_libtcl_la_DEPENDENCIES+=debug/libtclscr.la
endif

if VELOC_SUPPORT
common_debug_CPPFLAGS+=-DVELOC_BACKEND
common_debug_CXXFLAGS+=-DVELOC_BACKEND
noinst_LTLIBRARIES+= debug/libtclveloc.la
debug_libtclveloc_la_CPPFLAGS=$(common_includes) $(common_debug_CPPFLAGS) @mpiinc@ @velocinc@
debug_libtclveloc_la_CXXFLAGS=$(common_includes) $(common_debug_CXXFLAGS)
debug_libtclveloc_la_LDFLAGS=$(AM_LDFLAGS) @veloclib@ 
debug_libtclveloc_la_LIBADD=@veloclibs@
debug_libtclveloc_la_SOURCES=$(veloc_sources)
debug_libtcl_la_LIBADD+=debug/libtclveloc.la
debug_libtcl_la_DEPENDENCIES+=debug/libtclveloc.la
endif

debug_libtcl_la_CPPFLAGS=$(common_includes) $(common_debug_CPPFLAGS)
debug_libtcl_la_CXXFLAGS=$(common_includes) $(common_debug_CXXFLAGS)
debug_libtcl_la_LDFLAGS=$(AM_LDFLAGS) $(ignore_muldefs) -Wl,-rpath,$(libdir)/debug
debug_libtcl_la_SOURCES=$(common_sources)
nodist_debug_libtcl_la_SOURCES=$(nodist_common_sources)
endif

if is_performance_enabled
performance_LTLIBRARIES+=performance/libtcl.la
performance_libtcl_la_LIBADD=$(common_libadd) @tcl_config_libs_performance@
performance_libtcl_la_DEPENDENCIES=$(common_libadd) @tcl_config_libs_performance@

if FTI_SUPPORT
common_performance_CPPFLAGS+=-DFTI_BACKEND
common_performance_CXXFLAGS+=-DFTI_BACKEND
noinst_LTLIBRARIES+= performance/libtclfti.la
performance_libtclfti_la_CPPFLAGS=$(common_includes) $(common_performance_CPPFLAGS) @mpiinc@ @ftiinc@
performance_libtclfti_la_CXXFLAGS=$(common_includes) $(common_performance_CXXFLAGS)
performance_libtclfti_la_LDFLAGS=$(AM_LDFLAGS) @ftilib@ 
performance_libtclfti_la_LIBADD=@ftilibs@
performance_libtclfti_la_SOURCES=$(fti_sources)
performance_libtcl_la_LIBADD+=performance/libtclfti.la
performance_libtcl_la_DEPENDENCIES+=performance/libtclfti.la
endif

if SCR_SUPPORT
common_performance_CPPFLAGS+=-DSCR_BACKEND
common_performance_CXXFLAGS+=-DSCR_BACKEND
noinst_LTLIBRARIES+= performance/libtclscr.la
performance_libtclscr_la_CPPFLAGS=$(common_includes) $(common__CPPFLAGS) @mpiinc@ @scrinc@
performance_libtclscr_la_CXXFLAGS=$(common_includes) $(common_performance_CXXFLAGS)
performance_libtclscr_la_LDFLAGS=$(AM_LDFLAGS) @scrlib@ 
performance_libtclscr_la_LIBADD=@scrlibs@
performance_libtclscr_la_SOURCES=$(scr_sources)
performance_libtcl_la_LIBADD+=performance/libtclscr.la
performance_libtcl_la_DEPENDENCIES+=performance/libtclscr.la
endif

if VELOC_SUPPORT
common_performance_CPPFLAGS+=-DVELOC_BACKEND
common_performance_CXXFLAGS+=-DVELOC_BACKEND
noinst_LTLIBRARIES+= performance/libtclveloc.la
performance_libtclveloc_la_CPPFLAGS=$(common_includes) $(common__CPPFLAGS) @mpiinc@ @velocinc@
performance_libtclveloc_la_CXXFLAGS=$(common_includes) $(common_performance_CXXFLAGS)
performance_libtclveloc_la_LDFLAGS=$(AM_LDFLAGS) @veloclib@ 
performance_libtclveloc_la_LIBADD=@veloclibs@
performance_libtclveloc_la_SOURCES=$(veloc_sources)
performance_libtcl_la_LIBADD+=performance/libtclveloc.la
performance_libtcl_la_DEPENDENCIES+=performance/libtclveloc.la
endif

performance_libtcl_la_CPPFLAGS=$(common_includes) $(common_performance_CPPFLAGS)
performance_libtcl_la_CXXFLAGS=$(common_includes) $(common_performance_CXXFLAGS)
performance_libtcl_la_LDFLAGS=$(AM_LDFLAGS) $(ignore_muldefs) -Wl,-rpath,$(libdir)/performance
performance_libtcl_la_SOURCES=$(common_sources)
nodist_performance_libtcl_la_SOURCES=$(nodist_common_sources)
endif

