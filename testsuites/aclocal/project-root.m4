dnl
dnl $Id: project-root.m4,v 1.4 2010/07/27 18:17:37 joel Exp $
dnl 

AC_DEFUN([RTEMS_PROJECT_ROOT],
[dnl
AC_REQUIRE([RTEMS_TOP])

PACKHEX="\$(PROJECT_TOPdir)/tools/build/packhex"
AC_SUBST(PACKHEX)

BIN2C="\$(PROJECT_TOPdir)/tools/build/rtems-bin2c"
AC_SUBST(BIN2C)
])

