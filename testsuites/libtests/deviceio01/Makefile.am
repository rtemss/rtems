##
## $Id: Makefile.am,v 1.2 2011/06/20 08:53:02 ralf Exp $
##

rtems_tests_PROGRAMS = deviceio01
deviceio01_SOURCES = init.c test_driver.c
deviceio01_SOURCES += test_driver.h

dist_rtems_tests_DATA = deviceio01.scn
dist_rtems_tests_DATA += deviceio01.doc

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

AM_CPPFLAGS += -I$(top_srcdir)/../support/include

LINK_OBJS = $(deviceio01_OBJECTS) $(deviceio01_LDADD)
LINK_LIBS = $(deviceio01_LDLIBS)

deviceio01$(EXEEXT): $(deviceio01_OBJECTS) $(deviceio01_DEPENDENCIES)
	@rm -f deviceio01$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am
