## Process this file with autoconf to produce a configure script.
##
## $Id: configure.ac,v 1.26 2011/02/02 15:00:26 ralf Exp $

AC_PREREQ([2.68])
AC_INIT([rtems-c-src-lib-libbsp-sh-gensh1],[_RTEMS_VERSION],[http://www.rtems.org/bugzilla])
AC_CONFIG_SRCDIR([bsp_specs])
RTEMS_TOP(../../../../../..)

RTEMS_CANONICAL_TARGET_CPU
AM_INIT_AUTOMAKE([no-define nostdinc foreign 1.11.1])
RTEMS_BSP_CONFIGURE

RTEMS_PROG_CC_FOR_TARGET
RTEMS_CANONICALIZE_TOOLS
RTEMS_PROG_CCAS

## bsp-specific options
RTEMS_BSPOPTS_SET([CPU_CLOCK_RATE_HZ],[*],[20000000])
RTEMS_BSPOPTS_HELP([CPU_CLOCK_RATE_HZ],[cpu clock rate in HZ])

RTEMS_BSPOPTS_SET([START_HW_INIT],[*],[])
RTEMS_BSPOPTS_HELP([START_HW_INIT],
[If defined, selects whether 'early_hw_init()' is called from 'start.S';
 'bsp_hw_init()' is always called from 'bspstart.c'])

## Used in scitab/Makefile.am
AC_SUBST(CPU_CLOCK_RATE_HZ)

RTEMS_BSP_CLEANUP_OPTIONS(0, 1)

# Explicitly list all Makefiles here
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
