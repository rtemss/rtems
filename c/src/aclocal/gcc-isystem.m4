dnl
dnl $Id: gcc-isystem.m4,v 1.2 2003/11/26 06:18:03 ralf Exp $
dnl
dnl Check whether the gcc accepts -isystem
dnl

AC_DEFUN([RTEMS_GCC_ISYSTEM],
[AC_REQUIRE([RTEMS_PROG_CC])
AC_CACHE_CHECK(whether $CC accepts -isystem,rtems_cv_gcc_isystem,
[
rtems_cv_gcc_isystem=no
if test x"$GCC" = x"yes"; then
cat << EOF > conftest.h
int conftest123();
EOF
cat << EOF > conftest.c
#include <conftest.h>
int conftest123() {}
EOF
  if test -z "`${CC} -isystem./ -c conftest.c 2>&1`";then
    rtems_cv_gcc_isystem=yes
  fi
fi
rm -f conftest*
])])
