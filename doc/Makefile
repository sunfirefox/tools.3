#
#	Makefile -- Documentation makefile
#
#	Copyright (c) Embedthis Software LLC, 2003-2012. All Rights Reserved.
#

include		.makedep

PRE_DIRS	+= api product

gen: 
	make -C api
	make -C product
	make patch list

patch: 
	@echo -e "\n  # Perform DSI patching\n"
	cp dsi/banner.html /tmp/dsi$$.tmp 
	sed -e "s^TITLE-->.*^TITLE-->$(BLD_NAME) Preview $(BLD_VERSION)^g;" < /tmp/dsi$$.tmp > dsi/banner.html
	rm -f /tmp/dsi$$.tmp
	( find api -name '*.html' ; find guide licenses product ref -name '*.html' ) | dsi -v -I.

tidy:
	chmod +w *.html
	find . -name '*.html' -print | egrep -v 'dsi|old|sav|archive|api/gen' | \
	while read f ; do \
		echo tidy -q -config tidy.conf "$$f" ; \
		tidy -q -config tidy.conf "$$f" ; \
	done

#
#   Local variables:
#   tab-width: 4
#   c-basic-offset: 4
#   End:
#   vim: sw=4 ts=4 noexpandtab
#
