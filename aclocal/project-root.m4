dnl
dnl $Id: project-root.m4,v 1.8 2010/07/27 18:17:46 joel Exp $
dnl 

dnl
dnl PROJECT_TOPdir     .. relative path to the top of the build-tree
dnl PROJECT_ROOT       .. relative path to the top of the temporary
dnl                       installation directory inside the build-tree
dnl RTEMS_TOPdir       .. relative path of a subpackage's configure.in to the
dnl                       toplevel configure.in of the source-tree
dnl RTEMS_ROOT         .. path to the top of a bsp's build directory
dnl                       [Applied by custom/*.cfg, depredicated otherwise]
dnl

AC_DEFUN([RTEMS_PROJECT_ROOT],
[dnl
AC_REQUIRE([RTEMS_TOP])

PACKHEX="\$(PROJECT_TOPdir)/tools/build/packhex"
AC_SUBST(PACKHEX)

BIN2C="\$(PROJECT_TOPdir)/tools/build/rtems-bin2c"
AC_SUBST(BIN2C)
])

