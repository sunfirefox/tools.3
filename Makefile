# 
#	Makefile -- Top level Makefile
#
#	Copyright (c) Embedthis Software LLC, 2003-2012. All Rights Reserved.
#
#	Standard Make targets supported are:
#	
#		make 						# Does a "make compile"
#		make clean					# Removes generated objects
#		make compile				# Compiles the source
#		make depend					# Generates the make dependencies
#		make test 					# Runs unit tests
#		make leakTest 				# Runs memory leak tests
#		make loadTest 				# Runs load tests
#		make benchmark 				# Runs benchmarks
#		make package				# Creates an installable package
#
#	Additional targets for this makefile:
#
#		make build					# Do a clean build
#
#	Installation targets. Use "make DESTDIR=myDir" to do a custom local
#		install:
#
#		make install				# Call install-binary
#		make install-release		# Install release files (README.TXT etc)
#		make install-binary			# Install binary files
#		make install-dev			# Install development libraries and headers
#		make install-doc			# Install documentation
#		make install-samples		# Install samples
#		make install-src			# Install source code
#		make install-all			# Install everything except source code
#
#	To remove, use make uninstall-ITEM, where ITEM is a component above.
#

include		build/make/Makefile.top

config:
	./configure
	make depend clean >/dev/null

config64:
	./configure --host=x86_64-apple-darwin --build=x86_64-apple-darwin

cross64:
	./configure --static --host=x86_64-apple-darwin

vx:
	unset WIND_HOME WIND_BASE ; SEARCH_PATH=/tornado ./configure --host=i386-wrs-vxworks

sync: dummy

#
#   Local variables:
#   tab-width: 4
#   c-basic-offset: 4
#   End:
#   vim: sw=4 ts=4 noexpandtab
#
