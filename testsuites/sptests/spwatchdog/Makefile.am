##
## $Id: Makefile.am,v 1.3 2009/11/09 14:25:28 joel Exp $
##

MANAGERS = all

rtems_tests_PROGRAMS = spwatchdog
spwatchdog_SOURCES = init.c task1.c system.h prtime.c delay.c

dist_rtems_tests_DATA = spwatchdog.scn
dist_rtems_tests_DATA += spwatchdog.doc

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

spwatchdog_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

AM_CPPFLAGS += -I$(top_srcdir)/../support/include

LINK_OBJS = $(spwatchdog_OBJECTS) $(spwatchdog_LDADD)
LINK_LIBS = $(spwatchdog_LDLIBS)

spwatchdog$(EXEEXT): $(spwatchdog_OBJECTS) $(spwatchdog_DEPENDENCIES)
	@rm -f spwatchdog$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am
