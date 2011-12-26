THIS IS JUST A TEMPLATE --

Embedthis EJScript 
README.TXT

Welcome to the Embedthis EJScript distribution. This document contains details 
regarding the installation procedure for the binary Embedthis EJScript package.
This package contains a pre-built stand-alone (binary) web server and the 
development libraries and headers needed to embed EJScript in an application.
Once installed, you may read the EJScript online documentation and samples for
further information. You can also read the documentation for the latest release
online at:

    http://www.embedthis.com/products/ejscript/doc/index.html

This software is copyrighted and distributed under license. Please read the 
LICENSE.TXT for details.


Table of Contents
-----------------

* System Requirements
* Linux Release Details
* Windows Release Details
* VxWorks Release Details
* Building the Source Code
* License and Copyright Information

System Requirements
-------------------

Operating System Support

    * Linux 2.4, 2.6 (x86,arm,ppc,sparc,xscale,mips)
    * Windows XP (x86)
    * Windows 2000 (x86)
    * Solaris (sparc,x86)
    * VxWorks (x86,arm,ppc,sparc,xscale,mips)
    * Mac OSX (PPC) -- experimental

Run-time System Requirements

To run Embedthis EJScript, your system will need at least the following

    * 600 KB spare memory
    * 300 KB disk space
    * TCP/IP network stack

To develop applications that use Embedthis EJScript you will need an additional

    * 8 MB disk space

To rebuild EJScript from source code, you will need at least

    * 20 MB disk space


Development Environment Platform Support

If you wish to embed EJScript in your application, build the samples or rebuild 
Embedthis EJScript from source code, you will need to use a C/C++ compiler and 
associated development tools. Several development environments are supported. 
You may choose any of the following:

    * Linux GNU tools

    * Windows Visual Studio (Visual Studio 6 or Windows Visual Studio .NET 2003)
      This also requires the Cygwin UNIX emulation tools. See either 
      www.cygwin.com or download the WinTools from:

      http://www.embedthis.com/software/WinTools.zip


Linux Release Details
---------------------

Installing Embedthis EJScript

The installation distribution includes sub-packages containing pre-built 
binaries, development libraries, headers, documentation and samples. You can 
selectively install the sub-packages or you can install the complete 
distribution.

For those looking to build from source code, you will need to download the 
separate source code distribution. The product documentation describes how 
to build from source. 

The Embedthis EJScript install distribution for LINUX is published in two formats:

    * RPM format

    * Tar format for custom/self installs.

It is recommended that you use the RPM format if your system supports the RPM 
package standard.

    * The RPM image is: ejs-VERSION-NUMBER-LINUX-i386.rpm.tar.gz

    * The Self install image is: ejs-VERSION-NUMBER-LINUX-i386.self.tar.gz

The RPM format will register the software installation with the system's RPM 
manager so that you can query, verify, and easily manage the software on your 
system. 

The self-install format consists of tar archives that you can manually 
extract for maximum control over the placement of the product files. You can 
however, still use the install script with the self-install distribution if 
your system does not support RPM.

To install the Linux RPM image:

   1. If you are installing the binary package, you will need to login as 
       root or attain root privilege when you execute the install script.

   2. Uncompress the image by typing

      gunzip ejs-VERSION-BUILD-LINUX-i386.rpm.tar.gz

   3. Extract the top level files by typing

      tar xvf ejs-VERSION-BUILD-LINUX-i386.rpm.tar

   4. ./install


To install the Linux Self-Install image:

   1. If you are installing the binary package, you will need to login as root 
      or attain root privilege when you execute the install script.

   2. gunzip ejs-VERSION-BUILD-LINUX-i386.self.tar.gz

   3. tar xvf ejs-VERSION-BUILD-LINUX-i386.self.tar

   4. cd {Desired-Directory-For-Binaries}

   5. gunzip ejs-VERSION-BUILD.tar.gz

   6. tar xvf ejs-VERSION-BUILD.tar


Removing Embedthis EJScript

   1. Login as root

   2. Change directory to the installation directory for EJScript. This is 
      usually /etc/ejs

   3. Run the remove script in the install directory for EJScript by typing 

      ./remove


Windows Release Details
-----------------------

The installation distribution includes sub-packages containing pre-built 
binaries, development libraries and headers, documentation and samples. 
You can selectively install the sub-packages or you can install the complete 
distribution.

Installing Embedthis EJScript

The Embedthis EJScript Server install distribution for Windows is published in 
one format:

    * A ZIPped Windows installer executable named:

      ejs-VERSION-BUILD-WIN-i386.exe.zip

The image contains the binary distribution, libraries, headers, documentation 
and samples distribution in the one package. During installation you will have 
the option of installing the full package or just the binary or documentation 
and samples.

To install the Windows Installer image

   1. Login with administrator privileges. This is necessary as the binary 
      installation needs to install a Windows Service.

   2. Use WinZip or equivalent software to extract the README.TXT and 
      setup.exe from the zip archive.

   3. Select Run from the Start menu and browse to the location holding the 
      setup.exe install image and select it.

   4. Click OK.


Removing Embedthis EJScript

If you installed the custom image, you will need to remove EJScript manually. If 
you installed the Windows Installer image, follow these steps to remove EJScript.

   1. Login with administrator privileges

   2. Run the Add / Remove Programs applet from the control panel.

   3. Select the Embedthis EJScript Server and choose remove.


Running EJScript

The EJScript product installation includes a simple command line interpreter that
can be invoked by typing:

	ejs

This command responds with the following prompt:

ejs>

EJScript commands can be entered and results will be echoed to the console.
See the user documentation for further details.



Building the Source Code
------------------------

If you wish to rebuild the EJScript product from the distributed source code, 
please download the source code distribution from the Embedthis web site. Then
read "Building from Source" in the EJScript product documentation for an 
explanation of the necessary steps to successfully rebuild the product.


License and Copyright Information
---------------------------------

This software is supplied under license. Both a GNU and commercial license are 
available. Please read LICENSE.TXT for details. This documentation and the 
software described in this document may be used and copied only in accordance 
with the terms of the accompanying license agreement. Product and technical 
information in this document is subject to change without notice and does not 
represent a commitment on the part of Embedthis Software LLC.

Copyright (c) Embedthis Software LLC, 2003-2012. All Rights Reserved.

Embedthis is a trademark of Embedthis Software LLC. Embedthis, EJScript, ESP and 
EGI are trademarks of Embedthis Software. All other brand or product names are 
the trademarks or registered trademarks of their respective holders.


Embedthis Software, LLC.
7427 Orin Court N
Seattle, WA 98103.
+1 (425) 329-3490
www.embedthis.com
info@embedthis.com
