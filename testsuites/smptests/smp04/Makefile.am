##
##  $Id: Makefile.am,v 1.2 2011/07/29 12:29:34 jennifer Exp $
##

MANAGERS = all

rtems_tests_PROGRAMS = smp04
smp04_SOURCES = init.c system.h ../../support/src/locked_print.c

dist_rtems_tests_DATA = smp04.scn
dist_rtems_tests_DATA += smp04.doc

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

AM_CPPFLAGS += -I$(top_srcdir)/../support/include
AM_CPPFLAGS += -DSMPTEST 

smp04_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

LINK_OBJS = $(smp04_OBJECTS) $(smp04_LDADD)
LINK_LIBS = $(smp04_LDLIBS)

smp04$(EXEEXT): $(smp04_OBJECTS) $(smp04_DEPENDENCIES)
	@rm -f smp04$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am
