##
## $Id: Makefile.am,v 1.4 2010/06/23 22:49:58 joel Exp $
##

MANAGERS = all

rtems_tests_PROGRAMS = psxkey01
psxkey01_SOURCES = init.c task.c system.h ../include/pmacros.h \
     ../../support/src/test_support.c


dist_rtems_tests_DATA = psxkey01.scn

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

psxkey01_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

AM_CPPFLAGS += -I$(top_srcdir)/include
AM_CPPFLAGS += -I$(top_srcdir)/../support/include

LINK_OBJS = $(psxkey01_OBJECTS) $(psxkey01_LDADD)
LINK_LIBS = $(psxkey01_LDLIBS)

psxkey01$(EXEEXT): $(psxkey01_OBJECTS) $(psxkey01_DEPENDENCIES)
	@rm -f psxkey01$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am
