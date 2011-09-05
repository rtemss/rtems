##
## $Id: Makefile.am,v 1.14 2011/06/18 07:18:28 ralf Exp $
##

include_libcpudir = $(includedir)/libcpu

EXTRA_DIST =
EXTRA_DIST += shared/include/cache.h
EXTRA_DIST += shared/src/cache_aligned_malloc.c
EXTRA_DIST += shared/src/cache_manager.c

SUBDIRS = @libcpu_cpu_subdir@
DIST_SUBDIRS = @libcpu_cpu_subdir@

include $(top_srcdir)/automake/subdirs.am
include $(top_srcdir)/automake/local.am
