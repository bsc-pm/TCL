AC_INIT([cplib], [0.10a], [mmaronas@bsc.es])
AC_LANG([C++])
AC_CONFIG_SRCDIR([src/Checkpoint.cpp])
AC_DEFINE_UNQUOTED([NANOX_CONFIGURE_ARGS], ["$0 $@"], [Configure line])

# Environment
AC_CANONICAL_BUILD
AC_CANONICAL_SYSTEM
AC_CANONICAL_TARGET

# Automake initialization
AM_INIT_AUTOMAKE([-Wall dist-bzip2 -Wno-portability subdir-objects])
AC_CONFIG_MACRO_DIR([m4])

# Enable silent rules if available
supported_silent_rules=1
m4_ifdef([AM_SILENT_RULES],
         [AM_SILENT_RULES([yes])],
         [supported_silent_rules=0])

AM_CONDITIONAL([SUPPORTED_SILENT_RULES], test x$supported_silent_rules = x1)

# Debian release
AC_CHECK_PROG([DEB_RELEASE], [lsb_release], [$(lsb_release -sc)], [])
AC_SUBST([DEB_RELEASE])

# Set compiler default flags
: ${CFLAGS=""}
: ${CXXFLAGS=""}

# ------------------
# Check for programs
# ------------------
 AC_PROG_CC
 AC_PROG_CPP
 
 AC_PROG_CXX
 AC_PROG_CXXCPP
 
 AC_PROG_LD
 AM_PROG_AS
 
 AC_PROG_SED

 # AM_PROG_AR must be called before LT_INIT or a warning ensues
 m4_ifdef([AM_PROG_AR], [AM_PROG_AR])
 # Turn off static libraries.
 LT_INIT([disable-static])

# --------------------------------
# Compiler and flag checks
# --------------------------------

# Check for header files
AC_HEADER_STDC

# Check for typedefs, structures, and compiler characteristics
AC_C_CONST

# Compiler dependent Configuration flags
AX_CONFIG_CC

# -------------------
# Check for libraries
# -------------------

# MPI
AX_CHECK_MPI

# Check for FTI library
AX_CHECK_FTI

# Check for SCR library
AX_CHECK_SCR

# Check either FTI or SCR is enabled
AX_CHECK_FTI_OR_SCR_ENABLED

# Build versions
AX_BUILD_VERSIONS

# Output files
AC_CONFIG_HEADERS([config.h])

AC_CONFIG_FILES([
                 Makefile
       ])

AC_OUTPUT

AS_ECHO(["
Configuration summary of Checkpoint Library
================================

Configured versions:      $VERSIONS
Extra options:            $OPTIONS"
])
