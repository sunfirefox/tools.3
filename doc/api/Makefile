#
#	Makefile -- API Documentation makefile
#
#	Copyright (c) Embedthis Software LLC, 2003-2012. All Rights Reserved.
#

include		.makedep

PRE_DIRS	+= gen*

gen:
	for f in $(PRE_DIRS) ; do \
		make -C $$f gen ; \
	done

tidy:
	tidy -q -config tidy.conf *.html

#
#   Local variables:
#   tab-width: 4
#   c-basic-offset: 4
#   End:
#   vim: sw=4 ts=4 noexpandtab
#
