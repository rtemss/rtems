##
## $Id: Makefile.am,v 1.2 2011/06/20 06:40:14 ralf Exp $
##

MANAGERS = all

rtems_tests_PROGRAMS = spintrcritical09
spintrcritical09_SOURCES = init.c ../spintrcritical_support/intrcritical.c
spintrcritical09_SOURCES += ../spintrcritical_support/intrcritical.h

dist_rtems_tests_DATA = spintrcritical09.scn
dist_rtems_tests_DATA += spintrcritical09.doc

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

spintrcritical09_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

AM_CPPFLAGS += -I$(top_srcdir)/../support/include
AM_CPPFLAGS += -I$(top_srcdir)/spintrcritical_support

LINK_OBJS = $(spintrcritical09_OBJECTS) $(spintrcritical09_LDADD)
LINK_LIBS = $(spintrcritical09_LDLIBS)

spintrcritical09$(EXEEXT): $(spintrcritical09_OBJECTS) $(spintrcritical09_DEPENDENCIES)
	@rm -f spintrcritical09$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am
