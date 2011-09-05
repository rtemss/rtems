Name:           i686-pc-mingw32-libs-helper
Version:        0.20090717.0
Release:        1%{?dist}
Summary:        RTEMS mingw32 runtime libs helper

Group:          Development
License:        GPLv3+
BuildRoot:      %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)

BuildArch:	noarch
BuildRequires:  mingw32-runtime
Requires:       mingw32-runtime
Provides:	i686-pc-mingw32-libs

%description
%{summary}

%prep
%setup -q -c -T -n %{name}-%{version}

%build

%files

%changelog
