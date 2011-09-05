##
## $Id: Makefile.am,v 1.3 2011/05/18 12:59:44 ralf Exp $
##

include $(top_srcdir)/automake/compile.am

include_rtemsdir = $(includedir)/rtems
include_rtems_HEADERS = rtems/asm.h

include_rtems_scoredir = $(includedir)/rtems/score
include_rtems_score_HEADERS = rtems/score/cpu.h
include_rtems_score_HEADERS += rtems/score/lm32.h
include_rtems_score_HEADERS += rtems/score/cpu_asm.h
include_rtems_score_HEADERS += rtems/score/types.h

noinst_LIBRARIES = libscorecpu.a
libscorecpu_a_SOURCES = cpu.c cpu_asm.S irq.c
libscorecpu_a_CPPFLAGS = $(AM_CPPFLAGS)

include $(srcdir)/preinstall.am
include $(top_srcdir)/automake/local.am
