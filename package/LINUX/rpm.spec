#
#	RPM spec file for the Embedthis AppWeb HTTP web server
#
Summary: !!BLD_NAME!! -- Embeddable HTTP Web Server
Name: !!BLD_PRODUCT!!
Version: !!BLD_VERSION!!
Release: !!BLD_NUMBER!!
License: Dual GPL/commercial
Group: Applications/Internet
URL: http://www.embedthis.com/appweb
Distribution: Embedthis
Vendor: Embedthis Software
BuildRoot: !!ROOT_DIR!!/RPM/BUILDROOT/!!BLD_PRODUCT!!-!!BLD_VERSION!!-!!BLD_NUMBER!!.!!BLD_CPU!!
AutoReqProv: no

%description
Embedthis AppWeb is an embeddable HTTP Web Server

%prep

%build

%install

%clean

%files -f binFiles.txt

%post
if [ -x /usr/bin/chcon ] ; then 
	for f in /usr/lib/!!BLD_PRODUCT!!/modules/*.so ; do
		chcon /usr/bin/chcon -t texrel_shlib_t $f
	done
fi

ldconfig /usr/lib/lib!!BLD_PRODUCT!!.so.?.?.?
ldconfig -n /usr/lib/!!BLD_PRODUCT!!
ldconfig -n /usr/lib/!!BLD_PRODUCT!!/modules

%preun

%postun

#
#	Dev package
#
%package dev
Summary: Embedthis AppWeb -- Development headers for Embedthis AppWeb
Group: Applications/Internet
Prefix: !!BLD_INC_PREFIX!!

%description dev
Development headers for the Embedthis AppWeb is an embedded HTTP web server.

%files dev -f devFiles.txt

#
#	Source package
#
%package src
Summary: Embedthis AppWeb -- Source code for Embedthis AppWeb
Group: Applications/Internet
Prefix: !!BLD_SRC_PREFIX!!

%description src
Source code for the Embedthis AppWeb, an embedded HTTP web server.

%files src -f srcFiles.txt

#
#	Documentation and Samples package
#
%package doc
Summary: Embedthis AppWeb -- Documentation and Samples for Embedthis AppWeb
Group: Applications/Internet
Prefix: !!BLD_DOC_PREFIX!!

%description doc
Documentation and samples for Embedthis AppWeb, an embedded HTTP web server.

%files doc -f docFiles.txt
