dnl
dnl $Id: canonical-target-name.m4,v 1.7 2011/02/25 06:17:36 ralf Exp $
dnl

dnl canonicalize target cpu
dnl NOTE: Most rtems targets do not fullfil autoconf's
dnl target naming conventions "processor-vendor-os"
dnl Therefore autoconf's AC_CANONICAL_TARGET will fail for them
dnl and we have to fix it for rtems ourselves 

AC_DEFUN([RTEMS_CANONICAL_TARGET_CPU],
[AC_REQUIRE([AC_CANONICAL_HOST])
AC_MSG_CHECKING(rtems target cpu)
case "${host}" in
*-*-rtems*)
	RTEMS_CPU="$host_cpu";;
*)
	;;
esac
AS_IF([test -n "$RTEMS_CPU"],
[dnl
AC_MSG_RESULT($RTEMS_CPU)],
[dnl
AC_MSG_RESULT([<none>])
AC_MSG_ERROR([unsupported host $host])])
AC_SUBST(RTEMS_CPU)
])
