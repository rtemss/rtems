##
##  $Id: Makefile.am,v 1.12 2011/05/17 20:39:40 joel Exp $
##

ACLOCAL_AMFLAGS = -I ../../../aclocal

noinst_PROGRAMS = shgen

shgen_SOURCES = sci.h sci.c shgen.c

if HELP2MAN
man_MANS = shgen.1

shgen.1: shgen$(EXEEXT)
	$(HELP2MAN) -N ./shgen >$@
endif

include $(top_srcdir)/../../../automake/host.am
