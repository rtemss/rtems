##
## $Id: Makefile.am,v 1.4 2010/06/23 22:49:58 joel Exp $
##

MANAGERS = all

rtems_tests_PROGRAMS = psxmsgq02
psxmsgq02_SOURCES = init.c system.h ../include/pmacros.h \
     ../../support/src/test_support.c

dist_rtems_tests_DATA = psxmsgq02.scn

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

psxmsgq02_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

AM_CPPFLAGS += -I$(top_srcdir)/include
AM_CPPFLAGS += -I$(top_srcdir)/../support/include

LINK_OBJS = $(psxmsgq02_OBJECTS) $(psxmsgq02_LDADD)
LINK_LIBS = $(psxmsgq02_LDLIBS)

psxmsgq02$(EXEEXT): $(psxmsgq02_OBJECTS) $(psxmsgq02_DEPENDENCIES)
	@rm -f psxmsgq02$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am
