##
## $Id: Makefile.am,v 1.1 2009/07/09 19:02:40 joel Exp $
##

MANAGERS = all

rtems_tests_PROGRAMS = spthreadq01
spthreadq01_SOURCES = init.c

dist_rtems_tests_DATA = spthreadq01.scn
dist_rtems_tests_DATA += spthreadq01.doc

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

spthreadq01_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

AM_CPPFLAGS += -I$(top_srcdir)/../support/include

LINK_OBJS = $(spthreadq01_OBJECTS) $(spthreadq01_LDADD)
LINK_LIBS = $(spthreadq01_LDLIBS)

spthreadq01$(EXEEXT): $(spthreadq01_OBJECTS) $(spthreadq01_DEPENDENCIES)
	@rm -f spthreadq01$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am
