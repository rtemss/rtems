##
## $Id: Makefile.am,v 1.3 2010/06/23 22:49:58 joel Exp $
##

MANAGERS = all

rtems_tests_PROGRAMS = psxmutexattr01
psxmutexattr01_SOURCES = init.c

dist_rtems_tests_DATA = psxmutexattr01.scn
dist_rtems_tests_DATA += psxmutexattr01.doc

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

psxmutexattr01_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

AM_CPPFLAGS += -I$(top_srcdir)/include
AM_CPPFLAGS += -I$(top_srcdir)/../support/include

LINK_OBJS = $(psxmutexattr01_OBJECTS) $(psxmutexattr01_LDADD)
LINK_LIBS = $(psxmutexattr01_LDLIBS)

psxmutexattr01$(EXEEXT): $(psxmutexattr01_OBJECTS) $(psxmutexattr01_DEPENDENCIES)
	@rm -f psxmutexattr01$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am
