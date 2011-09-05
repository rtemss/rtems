#
# Please send bugfixes or comments to
# 	http://www.rtems.org/bugzilla
#

%define _prefix                 /opt/rtems-4.11
%define _exec_prefix            %{_prefix}
%define _bindir                 %{_exec_prefix}/bin
%define _sbindir                %{_exec_prefix}/sbin
%define _libexecdir             %{_exec_prefix}/libexec
%define _datarootdir            %{_prefix}/share
%define _datadir                %{_datarootdir}
%define _sysconfdir             %{_prefix}/etc
%define _sharedstatedir         %{_prefix}/com
%define _localstatedir          %{_prefix}/var
%define _includedir             %{_prefix}/include
%define _libdir                 %{_exec_prefix}/%{_lib}
%define _mandir                 %{_datarootdir}/man
%define _infodir                %{_datarootdir}/info
%define _localedir              %{_datarootdir}/locale

%ifos cygwin cygwin32 mingw mingw32
%define _exeext .exe
%define debug_package           %{nil}
%define _libdir                 %{_exec_prefix}/lib
%else
%define _exeext %{nil}
%endif

%ifos cygwin cygwin32
%define optflags -O3 -pipe -march=i486 -funroll-loops
%endif

%ifos mingw mingw32
%if %{defined _mingw32_cflags}
%define optflags %{_mingw32_cflags}
%else
%define optflags -O2 -g -pipe -Wall -Wp,-D_FORTIFY_SOURCE=2 -fexceptions --param=ssp-buffer-size=4 -mms-bitfields
%endif
%endif

%if "%{_build}" != "%{_host}"
%define _host_rpmprefix %{_host}-
%else
%define _host_rpmprefix %{nil}
%endif


%define cpukit_pkgvers 4.9.99.0-20090206-2
%define cpukit_version 4.9.99.0
%define cpukit_rpmvers %{expand:%(echo "4.9.99.0-20090206-2" | tr - . )}

Name:         	rtems-4.11-sh-rtems4.11-cpukit
Summary:      	sh-rtems4.11 cpukit

Group:	      	Development/Tools
Version:        %{cpukit_rpmvers}
Release:      	1%{?dist}
License:      	GPL
URL:		http://cpukit.gnu.org
BuildRoot:	%{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
BuildArch:	noarch

%define debug_package %{nil}

BuildRequires:	rtems-4.11-sh-rtems4.11-gcc

Source0: 	ftp://ftp.rtems.org/pub/rtems/SOURCES/4.11/rtems-%{cpukit_pkgvers}.tar.bz2

%description
RTEMS cpukit for sh-rtems4.11.
%prep
%setup -c -T -n %{name}-%{version}

%setup -q -T -D -n %{name}-%{version} -a0


%build
  export PATH="%{_bindir}:${PATH}"
  mkdir -p build

  cd build
  ../rtems-%{cpukit_version}/configure \
    --prefix=%{_prefix} \
    --target=sh-rtems4.11 \
    --enable-multilib \
    --disable-rtemsbsp

  make all RTEMS_BSP=
  cd ..

%install
  rm -rf $RPM_BUILD_ROOT
  export PATH="%{_bindir}:${PATH}"
  cd build
  make DESTDIR=$RPM_BUILD_ROOT install
  cd ..

  rm -rf $RPM_BUILD_ROOT%{_prefix}/share/man
  rm -rf $RPM_BUILD_ROOT%{_prefix}/bin
# Extract %%__os_install_post into os_install_post~
cat << \EOF > os_install_post~
%__os_install_post
EOF

# Generate customized brp-*scripts
cat os_install_post~ | while read a x y; do
case $a in
# Prevent brp-strip* from trying to handle foreign binaries
*/brp-strip*)
  b=$(basename $a)
  sed -e 's,find $RPM_BUILD_ROOT,find $RPM_BUILD_ROOT%_bindir $RPM_BUILD_ROOT%_libexecdir,' $a > $b
  chmod a+x $b
  ;;
# Fix up brp-compress to handle %%_prefix != /usr
*/brp-compress*)
  b=$(basename $a)
  sed -e 's,\./usr/,.%{_prefix}/,g' < $a > $b
  chmod a+x $b
  ;;
esac
done

sed -e 's,^[ ]*/usr/lib/rpm.*/brp-strip,./brp-strip,' \
  -e 's,^[ ]*/usr/lib/rpm.*/brp-compress,./brp-compress,' \
< os_install_post~ > os_install_post 
%define __os_install_post . ./os_install_post


cat << EOF > %{_builddir}/%{name}-%{version}/find-provides
#!/bin/sh
grep -E -v '^${RPM_BUILD_ROOT}%{_exec_prefix}/sh-rtems4.11/(lib|include|sys-root)' \
  | grep -v '^${RPM_BUILD_ROOT}%{cpukitlib}/sh-rtems4.11/' | %__find_provides
EOF
chmod +x %{_builddir}/%{name}-%{version}/find-provides
%define __find_provides %{_builddir}/%{name}-%{version}/find-provides

cat << EOF > %{_builddir}/%{name}-%{version}/find-requires
#!/bin/sh
grep -E -v '^${RPM_BUILD_ROOT}%{_exec_prefix}/sh-rtems4.11/(lib|include|sys-root)' \
  | grep -v '^${RPM_BUILD_ROOT}%{cpukitlib}/sh-rtems4.11/' | %__find_requires
EOF
chmod +x %{_builddir}/%{name}-%{version}/find-requires
%define __find_requires %{_builddir}/%{name}-%{version}/find-requires

%clean
  rm -rf $RPM_BUILD_ROOT

%description -n rtems-4.11-sh-rtems4.11-cpukit
RTEMS cpukit for target sh-rtems4.11.

%files -n rtems-4.11-sh-rtems4.11-cpukit
%defattr(-,root,root)
%dir %{_prefix}
%{_prefix}/sh-rtems4.11
# Violates the FHS
%exclude %{_prefix}/make
