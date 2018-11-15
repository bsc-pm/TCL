#####################################################################################
#      Copyright 2015 Barcelona Supercomputing Center                               #
#                                                                                   #
#      This file is part of the NANOS++ library.                                    #
#                                                                                   #
#      NANOS++ is free software: you can redistribute it and/or modify              #
#      it under the terms of the GNU Lesser General Public License as published by  #
#      the Free Software Foundation, either version 3 of the License, or            #
#      (at your option) any later version.                                          #
#                                                                                   #
#      NANOS++ is distributed in the hope that it will be useful,                   #
#      but WITHOUT ANY WARRANTY; without even the implied warranty of               #
#      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                #
#      GNU Lesser General Public License for more details.                          #
#                                                                                   #
#      You should have received a copy of the GNU Lesser General Public License     #
#      along with NANOS++.  If not, see <http://www.gnu.org/licenses/>.             #
#####################################################################################

EXTRA_DIST = ChangeLog

ACLOCAL_AMFLAGS=-I m4


END=

checkpointlibincludedir = $(includedir)/checkpoint_lib

checkpointlibinclude_HEADERS = \
	api/checkpoint_lib/bootstrap.h \
	$(END)

include_HEADERS = \
	api/checkpoint_lib.h \
	$(END)

common_includes=\
 -I$(top_builddir)\
 -I$(top_srcdir)/src/\
 $(END)

api_includes=\
 -I$(top_srcdir)/api/\
 $(END)

common_sources=\
    src/Bootstrap.cpp \
    src/Checkpoint.cpp \
    src/FTICheckpoint.hpp \
    src/FTICheckpoint.cpp \
    src/SCRCheckpoint.hpp \
    src/SCRCheckpoint.cpp \
	$(END)

fti_sources = \
    src/FTICheckpoint.hpp \
    src/FTICheckpoint.cpp \
    $(END)

scr_sources = \
    src/SCRCheckpoint.hpp \
    src/SCRCheckpoint.cpp \
    $(END)

AM_CPPFLAGS=@cc_dep_CPPFLAGS@ @mpiinc@ @ftiinc@ @scrinc@ $(common_includes) $(api_includes) -DLIBDIR='$(libdir)'
AM_CXXFLAGS=@cc_dep_CXXFLAGS@
AM_LDFLAGS=@mpilib@ @ftilib@ @scrlib@
LIBS+=@mpilibs@ @ftilibs@ @scrlibs@

common_performance_CPPFLAGS= $(AM_CPPFLAGS) @performance_CPPFLAGS@
common_debug_CPPFLAGS= $(AM_CPPFLAGS) @debug_CPPFLAGS@
common_performance_CXXFLAGS= $(AM_CXXFLAGS) @performance_CXXFLAGS@
common_debug_CXXFLAGS= $(AM_CXXFLAGS) @debug_CXXFLAGS@

debug_LTLIBRARIES=
performance_LTLIBRARIES=

noinst_LTLIBRARIES=

if is_debug_enabled
debug_LTLIBRARIES+=debug/libcheckpoint.la

if FTI_SUPPORT
noinst_LTLIBRARIES+= debug/libcheckpointfti.la
debug_libcheckpointfti_la_CPPFLAGS=$(common_includes) $(common_debug_CPPFLAGS) @mpiinc@ @ftiinc@
debug_libcheckpointfti_la_CXXFLAGS=$(common_includes) $(common_debug_CXXFLAGS)
debug_libcheckpointfti_la_LDFLAGS=$(AM_LDFLAGS) @ftilib@ 
debug_libcheckpointfti_la_LIBADD=@ftilibs@
debug_libcheckpointfti_la_SOURCES=$(fti_sources)
endif

if SCR_SUPPORT
noinst_LTLIBRARIES+= debug/libcheckpointscr.la
debug_libcheckpointscr_la_CPPFLAGS=$(common_includes) $(common_debug_CPPFLAGS) @mpiinc@ @scrinc@
debug_libcheckpointscr_la_CXXFLAGS=$(common_includes) $(common_debug_CXXFLAGS)
debug_libcheckpointscr_la_LDFLAGS=$(AM_LDFLAGS) @scrlib@ 
debug_libcheckpointscr_la_LIBADD=@scrlibs@
debug_libcheckpointscr_la_SOURCES=$(scr_sources)
endif

debug_libcheckpoint_la_CPPFLAGS=$(common_includes) $(common_debug_CPPFLAGS)
debug_libcheckpoint_la_CXXFLAGS=$(common_includes) $(common_debug_CXXFLAGS)
debug_libcheckpoint_la_LDFLAGS=$(AM_LDFLAGS) $(ignore_muldefs) -Wl,-rpath,$(libdir)/debug
debug_libcheckpoint_la_LIBADD=$(common_libadd) debug/libcheckpointfti.la debug/libcheckpointscr.la
debug_libcheckpoint_la_SOURCES=$(common_sources)
debug_libcheckpoint_la_DEPENDENCIES=$(common_libadd) @nanos_config_libs_debug@ debug/libcheckpointfti.la debug/libcheckpointscr.la
endif

if is_performance_enabled
performance_LTLIBRARIES+=performance/libcheckpoint.la

if FTI_SUPPORT
noinst_LTLIBRARIES+= performance/libcheckpointfti.la
performance_libcheckpointfti_la_CPPFLAGS=$(common_includes) $(common_performance_CPPFLAGS) @mpiinc@ @ftiinc@
performance_libcheckpointfti_la_CXXFLAGS=$(common_includes) $(common_performance_CXXFLAGS)
performance_libcheckpointfti_la_LDFLAGS=$(AM_LDFLAGS) @ftilib@ 
performance_libcheckpointfti_la_LIBADD=@ftilibs@
performance_libcheckpointfti_la_SOURCES=$(fti_sources)
endif

if SCR_SUPPORT
noinst_LTLIBRARIES+= performance/libcheckpointscr.la
performance_libcheckpointscr_la_CPPFLAGS=$(common_includes) $(common__CPPFLAGS) @mpiinc@ @scrinc@
performance_libcheckpointscr_la_CXXFLAGS=$(common_includes) $(common_performance_CXXFLAGS)
performance_libcheckpointscr_la_LDFLAGS=$(AM_LDFLAGS) @scrlib@ 
performance_libcheckpointscr_la_LIBADD=@scrlibs@
performance_libcheckpointscr_la_SOURCES=$(scr_sources)
endif

performance_libcheckpoint_la_CPPFLAGS=$(common_includes) $(common_performance_CPPFLAGS)
performance_libcheckpoint_la_CXXFLAGS=$(common_includes) $(common_performance_CXXFLAGS)
performance_libcheckpoint_la_LDFLAGS=$(AM_LDFLAGS) $(ignore_muldefs) -Wl,-rpath,$(libdir)/performance
performance_libcheckpoint_la_LIBADD=$(common_libadd) @nanos_config_libs_performance@ performance/libcheckpointfti.la performance/libcheckpointscr.la
performance_libcheckpoint_la_SOURCES=$(common_sources)
performance_libcheckpoint_la_DEPENDENCIES=$(common_libadd) @nanos_config_libs_performance@ performance/libcheckpointfti.la performance/libcheckpointscr.la
endif

