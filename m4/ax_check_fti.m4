#
# SYNOPSIS
#
#   AX_CHECK_FTI
#
# DESCRIPTION
#
#   Check whether a valid FTI library is available, and the path to the headers 
#   and libraries are correctly specified.
#
# LICENSE
#
#   Copyright (c) 2018 Marcos Maronas <mmaronas@bsc.es>
#
#   This program is free software: you can redistribute it and/or modify it
#   under the terms of the GNU General Public License as published by the
#   Free Software Foundation, either version 3 of the License, or (at your
#   option) any later version.
#
#   This program is distributed in the hope that it will be useful, but
#   WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
#   Public License for more details.
#
#   You should have received a copy of the GNU General Public License along
#   with this program. If not, see <http://www.gnu.org/licenses/>.
#
#   As a special exception, the respective Autoconf Macro's copyright owner
#   gives unlimited permission to copy, distribute and modify the configure
#   scripts that are the output of Autoconf when processing the Macro. You
#   need not follow the terms of the GNU General Public License when using
#   or distributing such scripts, even though portions of the text of the
#   Macro appear in them. The GNU General Public License (GPL) does govern
#   all other use of the material that constitutes the Autoconf Macro.
#
#   This special excption to the GPL applies to versions of the Autoconf
#   Macro released by the Autoconf Archive. When you make and distribute a
#   modified version of the Autoconf Macro, you may extend this special
#   exception to the GPL to apply to your modified version as well.

AC_DEFUN([AX_CHECK_FTI],
[
#Check if FTI lib is installed.
AC_ARG_WITH(fti,
  [AS_HELP_STRING([--with-fti,--with-fti=PATH],
                [search in system directories or specify prefix directory for installed FTI package.])],
  [
    # Check if the user provided a valid PATH
    AS_IF([test -d "$withval"],[
      fti=yes
      fti_path_provided=yes
    ],[
      fti=$withval
      fti_path_provided=no
    ])dnl
  ],[
    # Default: check if fti is available
    fti=no
    fti_path_provided=no
  ])

# If the user specifies --with-fti, $with_fti value will be 'yes'
#                       --without-fti, $with_fti value will be 'no'
#                       --with-fti=somevalue, $with_fti value will be 'somevalue'
AS_IF([test "$fti_path_provided" = yes],[
  ftiinc="-I$with_fti/include"
  AS_IF([test -d $with_fti/lib64],
    [ftilib="-L$with_fti/lib64 -Wl,-rpath,$with_fti/lib64"],
    [ftilib="-L$with_fti/lib -Wl,-rpath,$with_fti/lib"])dnl
])dnl

AS_IF([test "$fti" = yes],[
  AX_VAR_PUSHVALUE([CPPFLAGS],[$CPPFLAGS $mpiinc $ftiinc])
  AX_VAR_PUSHVALUE([CXXFLAGS])
  AX_VAR_PUSHVALUE([LDFLAGS],[$LDFLAGS $mpilib $ftilib])
  AX_VAR_PUSHVALUE([LIBS],[$mpilibs])

  AS_IF([test x$mpi != xyes ], [
    AC_MSG_FAILURE([
------------------------------
FTI requires MPI support.
Please, provide a MPI library.
------------------------------])
  ])
    
  # Check for header
  AC_CHECK_HEADERS([fti.h],
    [fti=yes],
    [fti=no])

  # Look for fti_init function in libfti
  AS_IF([test "$fti" = yes],[
      AC_SEARCH_LIBS([FTI_Init],
                [fti],
                [fti=yes],
                [fti=no])
  ])dnl

  
  ftilibs="$LIBS"

  AX_VAR_POPVALUE([CPPFLAGS])
  AX_VAR_POPVALUE([CXXFLAGS])
  AX_VAR_POPVALUE([LDFLAGS])
  AX_VAR_POPVALUE([LIBS])
])dnl

AC_SUBST([ftiinc])
AC_SUBST([ftilib])
AC_SUBST([ftilibs])
AM_CONDITIONAL([FTI_SUPPORT],[test "$fti" = yes])

])dnl AX_CHECK_FTI

