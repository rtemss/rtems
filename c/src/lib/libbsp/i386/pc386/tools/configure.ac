## Process this file with autoconf to produce a configure script.
##
## $Id: configure.ac,v 1.16 2011/02/25 10:45:11 ralf Exp $

AC_PREREQ([2.68])
AC_INIT([rtems-c-src-lib-libbsp-i386-pc386-tools],[_RTEMS_VERSION],[http://www.rtems.org/bugzilla])
AC_CONFIG_SRCDIR([Spec.doc])
RTEMS_TOP(../../../../../../..)

CFLAGS="-g -O2 -Wall"

AM_INIT_AUTOMAKE([no-define foreign 1.11.1])
AM_MAINTAINER_MODE

RTEMS_ENV_RTEMSBSP
AC_PROG_CC

AC_CHECK_FUNCS(strtoul)

RTEMS_PROJECT_ROOT
RTEMS_TOOLPATHS

# Explicitly list all Makefiles here
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
