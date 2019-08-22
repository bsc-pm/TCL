#
# SYNOPSIS
#
#   AX_CHECK_FTI_OR_SCR_OR_VELOC_ENABLED
#
# DESCRIPTION
#
#   Check whether a valid FTI library or a valid SCR library or a valid VELOC library is available. 
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

AC_DEFUN([AX_CHECK_FTI_OR_SCR_OR_VELOC_ENABLED],
[
  AS_IF([test x$fti != xyes && test x$scr != xyes && test x$veloc != xyes ], [
    AC_MSG_FAILURE([
------------------------------
Either FTI or SCR or VELOC is required.
Please, provide a FTI/SCR/VELOC library.
------------------------------])
  ])

])dnl AX_CHECK_FTI_OR_SCR_VELOC_ENABLED

