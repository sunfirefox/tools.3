#
#	Makefile -- Documentation package makefile
#
#	Copyright (c) Embedthis Software LLC, 2003-2012. All Rights Reserved.
#

include		.makedep

compileExtra: file.list 

file.list: Makefile ../api/gen/$(BLD_PRODUCT)/doxygen.css
	@echo -e "\n  # Build file.list\n"
	cd .. ; \
		find . -type f -print | sort | \
		egrep '.html|.css|.png|.gif|.jpeg|.jpg|.TXT|.HTML|.pdf' | \
		egrep -v '\.#|\.swp|old|CVS|dsi|sav|allApi|masters|doxygen.css' | \
		egrep -v 'Master|\.hg|/package/|archive' | \
		egrep -v 'api/api.html|_notes|licenses|COPYRIGHT|LICENSE' | \
		egrep -v 'doxygen.png' >package/file.list

../api/gen/$(BLD_PRODUCT)/doxygen.css:

cleanExtra:
	rm -f file.list 

#
#   Local variables:
#   tab-width: 4
#   c-basic-offset: 4
#   End:
#   vim: sw=4 ts=4 noexpandtab
#
