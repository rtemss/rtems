##
##  $Id: Makefile.am,v 1.27 2011/05/05 22:29:23 joel Exp $
##

MANAGERS = all

rtems_tests_PROGRAMS = ticker
ticker_SOURCES = init.c tasks.c system.h

dist_rtems_tests_DATA = ticker.scn
dist_rtems_tests_DATA += ticker.doc

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

ticker_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

AM_CPPFLAGS += -I$(top_srcdir)/../support/include

LINK_OBJS = $(ticker_OBJECTS) $(ticker_LDADD)
LINK_LIBS = $(ticker_LDLIBS)

ticker$(EXEEXT): $(ticker_OBJECTS) $(ticker_DEPENDENCIES)
	@rm -f ticker$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am
