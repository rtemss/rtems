##
## $Id: Makefile.am,v 1.24 2010/04/30 14:30:09 sh Exp $
##

ACLOCAL_AMFLAGS = -I ../../../../aclocal

include $(top_srcdir)/../../../../automake/compile.am

include_bspdir = $(includedir)/bsp

dist_project_lib_DATA = bsp_specs

include_HEADERS = include/bsp.h
include_HEADERS += smc/smc.h
include_HEADERS += ../../shared/include/tm27.h

include_bsp_HEADERS =

nodist_include_HEADERS = include/bspopts.h
nodist_include_bsp_HEADERS = ../../shared/include/bootcard.h
DISTCLEANFILES = include/bspopts.h

nodist_include_HEADERS += ../../shared/include/coverhd.h

noinst_LIBRARIES = libbspstart.a
libbspstart_a_SOURCES = start/start.S
project_lib_DATA = start.$(OBJEXT)

dist_project_lib_DATA += startup/linkcmds

noinst_LIBRARIES += libbsp.a
libbsp_a_SOURCES =

# startup
libbsp_a_SOURCES += ../../shared/bsplibc.c ../../shared/bsppost.c \
    ../../shared/bsppredriverhook.c ../../shared/bspgetworkarea.c \
    ../../shared/bsppretaskinghook.c startup/bspstart.c \
    ../../shared/bspclean.c startup/bspreset.c \
    startup/memmap.c ../../shared/bootcard.c ../../shared/sbrk.c \
    ../../shared/gnatinstallhandler.c
# console
libbsp_a_SOURCES += console/uart.c ../../shared/console.c
# IRQ
include_bsp_HEADERS += ../../shared/include/irq-generic.h \
	../../shared/include/irq-info.h
libbsp_a_SOURCES += ../../shared/src/irq-generic.c \
	../../shared/src/irq-legacy.c \
	../../shared/src/irq-info.c \
	../../shared/src/irq-shell.c \
	../../shared/src/irq-server.c
# abort
libbsp_a_SOURCES += ../shared/abort/abort.c
# smc
libbsp_a_SOURCES += smc/smc.c smc/smc.h

libbsp_a_LIBADD = ../../../libcpu/@RTEMS_CPU@/shared/arm920.rel \
    ../../../libcpu/@RTEMS_CPU@/s3c24xx/clock.rel \
    ../../../libcpu/@RTEMS_CPU@/s3c24xx/timer.rel \
    ../../../libcpu/@RTEMS_CPU@/s3c24xx/irq.rel

include $(srcdir)/preinstall.am
include $(top_srcdir)/../../../../automake/local.am
