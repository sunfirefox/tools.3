#
#	Makefile for the Embedthis License Generation software
#
#	Copyright (c) Embedthis Software LLC, 2003-2012. All Rights Reserved.
#

BUILD_CROSS		:= 0
MAKE_IFLAGS		:= -I..

include 		.makedep

compileExtra: $(TARGETS) $(BLD_TOOLS_DIR)/genLicense$(BLD_EXE)

#
#	Build the license key generation program
#
$(BLD_TOOLS_DIR)/genLicense$(BLD_EXE): $(FILES) files
	@bld --executable $(BLD_TOOLS_DIR)/genLicense$(BLD_EXE) \
		$(BLD_OBJ_DIR)/genLicense$(BLD_OBJ) \
		$(BLD_OBJ_DIR)/mprLicense$(BLD_OBJ)

cleanExtra:
	@rm -f $(BLD_TOOLS_DIR)/genLicense$(BLD_EXE)

gen:
	genLicense -p appweb -v 2.0.0

oldTest:
	x=`genLicense -p appweb -v 2.0.0` ; \
	echo KEY is $$x ; \
	genLicense -d $$x

#
#   Local variables:
#   tab-width: 4
#   c-basic-offset: 4
#   End:
#   vim: sw=4 ts=4 noexpandtab
#
