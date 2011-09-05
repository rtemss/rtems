#
# Please send bugfixes or comments to
# 	http://www.rtems.org/bugzilla
#


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

%define netbsd_version 5.1
%define netbsd_rpmvers %{expand:%(echo 5.1 | tr - _)}

%define _use_internal_dependency_generator 0
%define __debug_install_post %{nil}

Name:		amd64-pc-netbsdelf5.1
Release:	0.20110320.0%{?dist}
License:	NetBSD
Group:		Development/Tools

BuildRoot:	%{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
BuildArch:	noarch

Version:      	%netbsd_rpmvers
Summary:      	amd64-pc-netbsdelf5.1 Libraries

Source0:	ftp://ftp.netbsd.org/pub/NetBSD/NetBSD-5.0.2/amd64/binary/sets/base.tgz
Source1:	ftp://ftp.netbsd.org/pub/NetBSD/NetBSD-5.0.2/amd64/binary/sets/comp.tgz

%description
amd64-pc-netbsdelf5.1 libraries.

%prep
%setup -q -c -T -n %{name}-%{version} -a 0 -a 1

%build
  # Setup sys-root (Usable for gcc >= 3.4)
  mkdir -p amd64-pc-netbsdelf5.1/sys-root
  %{__tar} cf - lib usr/lib usr/include | ( cd amd64-pc-netbsdelf5.1/sys-root ; %{__tar} xf -)

  pushd amd64-pc-netbsdelf5.1/sys-root/usr/lib > /dev/null
  # missing files
  rm -f lib*_p.*
  # not needed
  rm -rf aout compat

  # Fix up symlinks
  find -type l -exec ls -l {} \; | \
    while read a0 a1 a2 a3 a4 a5 a6 a7 a8 a9 aA ; do \
    case $aA in
    /lib* ) # link
       rm $a8;
       b=`basename $aA`
       ln -s ../../lib/$b $a8
       ;;
    esac
  done
  popd > /dev/null

%install
  rm -rf $RPM_BUILD_ROOT
  mkdir -p $RPM_BUILD_ROOT%{_prefix}
  cp -a amd64-pc-netbsdelf5.1 $RPM_BUILD_ROOT%{_prefix}

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
esac
done

sed -e 's,^[ ]*/usr/lib/rpm.*/brp-strip,./brp-strip,' \
< os_install_post~ > os_install_post 
%define __os_install_post . ./os_install_post


cat << EOF > %{_builddir}/%{name}-%{netbsd_rpmvers}/find-provides
#!/bin/sh
grep -E -v '^${RPM_BUILD_ROOT}%{_exec_prefix}/amd64-pc-netbsdelf5.1/(lib|include|sys-root)' \
  %{?_gcclibdir:| grep -v '^${RPM_BUILD_ROOT}%{_gcclibdir}/gcc/amd64-pc-netbsdelf5.1/'} | %__find_provides
EOF
chmod +x %{_builddir}/%{name}-%{netbsd_rpmvers}/find-provides
%define __find_provides %{_builddir}/%{name}-%{netbsd_rpmvers}/find-provides

cat << EOF > %{_builddir}/%{name}-%{netbsd_rpmvers}/find-requires
#!/bin/sh
grep -E -v '^${RPM_BUILD_ROOT}%{_exec_prefix}/amd64-pc-netbsdelf5.1/(lib|include|sys-root)' \
  %{?_gcclibdir:| grep -v '^${RPM_BUILD_ROOT}%{_gcclibdir}/gcc/amd64-pc-netbsdelf5.1/'} | %__find_requires
EOF
chmod +x %{_builddir}/%{name}-%{netbsd_rpmvers}/find-requires
%define __find_requires %{_builddir}/%{name}-%{netbsd_rpmvers}/find-requires

%ifnarch noarch
# Extract %%__debug_install_post into debug_install_post~
cat << \EOF > debug_install_post~
%__debug_install_post
EOF

# Generate customized debug_install_post script
cat debug_install_post~ | while read a x y; do
case $a in
# Prevent find-debuginfo.sh* from trying to handle foreign binaries
*/find-debuginfo.sh)
  b=$(basename $a)
  sed -e 's,find "$RPM_BUILD_ROOT" !,find "$RPM_BUILD_ROOT"%_bindir "$RPM_BUILD_ROOT"%_libexecdir !,' $a > $b
  chmod a+x $b
  ;;
esac
done

sed -e 's,^[ ]*/usr/lib/rpm/find-debuginfo.sh,./find-debuginfo.sh,' \
< debug_install_post~ > debug_install_post 
%define __debug_install_post . ./debug_install_post

%endif

%clean
  rm -rf $RPM_BUILD_ROOT

%package sys-root
Group: Development/Tools
Summary: amd64-pc-netbsdelf5.1 target files for gcc >= 3.4

%description sys-root
amd64-pc-netbsdelf5.1 target files for gcc >= 3.4

%files sys-root
%defattr(-,root,root,-)
%dir %{_prefix}/amd64-pc-netbsdelf5.1
%{_prefix}/amd64-pc-netbsdelf5.1/sys-root
