#
# SYNOPSIS
#
#   AX_CHECK_VELOC
#
# DESCRIPTION
#
#   Check whether a valid VELOC library is available, and the path to the headers 
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

AC_DEFUN([AX_CHECK_VELOC],
[
#Check if VELOC lib is installed.
AC_ARG_WITH(veloc,
  [AS_HELP_STRING([--with-veloc,--with-veloc=PATH],
                [search in system directories or specify prefix directory for installed VELOC package.])],
  [
    # Check if the user provided a valid PATH
    AS_IF([test -d "$withval"],[
      veloc=yes
      veloc_path_provided=yes
    ],[
      veloc=$withval
      veloc_path_provided=no
    ])dnl
  ],[
    # Default: check if veloc is available
    veloc=no
    veloc_path_provided=no
  ])

# If the user specifies --with-veloc, $with_veloc value will be 'yes'
#                       --without-veloc, $with_veloc value will be 'no'
#                       --with-veloc=somevalue, $with_veloc value will be 'somevalue'
AS_IF([test "$veloc_path_provided" = yes],[
  AS_IF([test -d $with_veloc/include64],
    [velocinc="-I$with_veloc/include64"],
    [velocinc="-I$with_veloc/include"])dnl

  AS_IF([test -d $with_veloc/lib],
    [veloclib="-L$with_veloc/lib -Wl,-rpath,$with_veloc/lib"],
    [veloclib="-L$with_veloc/lib64 -Wl,-rpath,$with_veloc/lib64"])dnl
])dnl

AS_IF([test "$veloc" = yes],[
  AX_VAR_PUSHVALUE([CPPFLAGS],[$CPPFLAGS $mpiinc $velocinc])
  AX_VAR_PUSHVALUE([CXXFLAGS])
  AX_VAR_PUSHVALUE([LDFLAGS],[$LDFLAGS $mpilib $veloclib])
  AX_VAR_PUSHVALUE([LIBS],[$mpilibs])

  # Check for header
  AC_CHECK_HEADERS([veloc.h],
    [veloc=yes],
    [veloc=no])

  # Look for veloc_init function in libveloc-client
  AS_IF([test "$veloc" = yes],[
      AC_SEARCH_LIBS([VELOC_Init],
                [veloc-client],
                [veloc=yes],
                [veloc=no])
  ])dnl

  # Look for module_manager::module_manager_t function in libveloc-modules
  AS_IF([test "$veloc" = yes],[
      AC_SEARCH_LIBS([_ZN16module_manager_tC1Ev],
                [veloc-modules],
                [veloc=yes],
                [veloc=no])
  ])dnl

  # If one of the previous tests were not satisfied, exit with an error message.
  AS_IF([test x$veloc != xyes],[
      AC_MSG_ERROR([
------------------------------
VELOC path was not correctly specified. 
Please, check that provided directories are correct.
------------------------------])
  ])dnl
  
  veloclibs="$LIBS"

  AX_VAR_POPVALUE([CPPFLAGS])
  AX_VAR_POPVALUE([CXXFLAGS])
  AX_VAR_POPVALUE([LDFLAGS])
  AX_VAR_POPVALUE([LIBS])
])dnl

AC_SUBST([velocinc])
AC_SUBST([veloclib])
AC_SUBST([veloclibs])
AM_CONDITIONAL([VELOC_SUPPORT],[test "$veloc" = yes])

])dnl AX_CHECK_VELOC

