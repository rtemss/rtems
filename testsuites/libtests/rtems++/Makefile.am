##
## $Id: Makefile.am,v 1.30 2010/06/23 23:26:08 joel Exp $
##

MANAGERS = event io msg sem signal timer rate_monotonic

if HAS_CXX
rtems_tests_PROGRAMS = rtems++
rtems___SOURCES = Init.cc Task1.cc Task2.cc Task3.cc System.h
endif

dist_rtems_tests_DATA = rtems++.scn
dist_rtems_tests_DATA += rtems++.doc

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

if HAS_CXX
rtems___LDLIBS = -lrtems++
AM_CPPFLAGS += -I$(top_srcdir)/../support/include

rtems___LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

LINK_OBJS = $(rtems___OBJECTS) $(rtems___LDADD)
LINK_LIBS = $(rtems___LDLIBS)

rtems++$(EXEEXT): $(rtems___OBJECTS) $(rtems___DEPENDENCIES)
	@rm -f rtems++$(EXEEXT)
	$(make-cxx-exe)
endif

include $(top_srcdir)/../automake/local.am
