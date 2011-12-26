#
#	Makefile -- Documentation makefile
#
#	Copyright (c) Embedthis Software LLC, 2003-2012. All Rights Reserved.
#

include		.makedep

compileExtra: index.html

index.html: $(BLD_TOP)/buildConfig.make Makefile
	cp index.html index.new
	sed 's/$(BLD_PRODUCT)Version.jpg.*\"/$(BLD_PRODUCT)Version.jpg?version=$(BLD_VERSION)-$(BLD_NUMBER)"/' < index.new >index.html
	cp index.html index.new
	sed "s/$(BLD_NAME) Documentation.*</$(BLD_NAME) Documentation $(BLD_VERSION)</" < index.new >index.html
	rm -f index.new

#
#   Local variables:
#   tab-width: 4
#   c-basic-offset: 4
#   End:
#   vim: sw=4 ts=4 noexpandtab
#
