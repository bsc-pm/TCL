#
# SYNOPSIS
#
#   AX_CHECK_SCR
#
# DESCRIPTION
#
#   Check whether a valid SCR library is available, and the path to the headers 
#   and libraries are correctly specified.
#
# LICENSE
#
#   Copyright (c) 2018 Marcos Maroñas <marcos.maronasbravo@bsc.es>
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

AC_DEFUN([AX_CHECK_SCR],
[
#Check if SCR lib is installed.
AC_ARG_WITH(scr,
  [AS_HELP_STRING([--with-scr,--with-scr=PATH],
                [search in system directories or specify prefix directory for installed SCR package.])],
  [
    # Check if the user provided a valid PATH
    AS_IF([test -d "$withval"],[
      scr=yes
      scr_path_provided=yes
    ],[
      scr=$withval
      scr_path_provided=no
    ])dnl
  ],[
    # Default: check if scr is available
    scr=no
    scr_path_provided=no
  ])

# If the user specifies --with-scr, $with_scr value will be 'yes'
#                       --without-scr, $with_scr value will be 'no'
#                       --with-scr=somevalue, $with_scr value will be 'somevalue'
AS_IF([test "$scr_path_provided" = yes],[
  scrinc="-I$with_scr/include"
  AS_IF([test -d $with_scr/lib64],
    [scrlib="-L$with_scr/lib64 -Wl,-rpath,$with_scr/lib64"],
    [scrlib="-L$with_scr/lib -Wl,-rpath,$with_scr/lib"])dnl
])dnl

AS_IF([test "$scr" = yes],[
  AX_VAR_PUSHVALUE([CPPFLAGS],[$CPPFLAGS $mpiinc $scrinc])
  AX_VAR_PUSHVALUE([CXXFLAGS])
  AX_VAR_PUSHVALUE([LDFLAGS],[$LDFLAGS $mpilib $scrlib])
  AX_VAR_PUSHVALUE([LIBS],[$mpilibs])

  AS_IF([test x$mpi != xyes ], [
    AC_MSG_FAILURE([
------------------------------
SCR requires MPI support.
Please, provide a MPI library.
------------------------------])
  ])
    
  # Check for header
  AC_CHECK_HEADERS([scr.h],
    [scr=yes],
    [scr=no])

  # Look for scr_init function in libscr
  AS_IF([test "$scr" = yes],[
      AC_SEARCH_LIBS([SCR_Init],
                [scr],
                [scr=yes],
                [scr=no])
  ])dnl

  # If one of the previous tests were not satisfied, exit with an error message.
  AS_IF([test x$scr != xyes],[
      AC_MSG_ERROR([
------------------------------
SCR path was not correctly specified. 
Please, check that provided directories are correct.
------------------------------])
  ])dnl
  
  scrlibs="$LIBS"

  AX_VAR_POPVALUE([CPPFLAGS])
  AX_VAR_POPVALUE([CXXFLAGS])
  AX_VAR_POPVALUE([LDFLAGS])
  AX_VAR_POPVALUE([LIBS])
])dnl

AC_SUBST([scrinc])
AC_SUBST([scrlib])
AC_SUBST([scrlibs])
AM_CONDITIONAL([SCR_SUPPORT],[test "$scr" = yes])

])dnl AX_CHECK_SCR

