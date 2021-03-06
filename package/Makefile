#
#	Makefile for the packages
#
#	Copyright (c) Embedthis Software LLC, 2003-2012. All Rights Reserved.
#

include 		.makedep 

PRE_DIRS		= $(BLD_HOST_OS)
BASE_NAME		:= "$(BLD_PRODUCT)-$(BLD_VERSION)-$(BLD_NUMBER)-$(BLD_HOST_DIST)-$(BLD_HOST_OS)-$(BLD_HOST_CPU)"
LAUNCH_BROWSER	:=  1
WIN_INS_DIR		:= c:/tmp/testInsAppweb
PKG_DIR			:= `pwd`/.tmp

ifeq	($(BLD_OS),1)
	PRIV		:= fakepriv
else
	PRIV		:= priv
endif

packageExtra:
	priv "OPTIONS=$(OPTIONS) TRACE=$(TRACE) \
		$(BLD_TOP)/build/bin/makeInstall --root=$(PKG_DIR) --package \"$(PACKS)\" ; \
		$(BLD_TOOLS_DIR)/makePackage --root=$(PKG_DIR)"

packageOnly:
	priv "$(BLD_TOOLS_DIR)/makePackage --root=$(PKG_DIR) $(PACKS)"

install-package: prep
	if [ $(BLD_HOST_OS) = WIN ] ; then \
		name="$(BASE_NAME).exe.zip" ; \
		rm -fr "$(WIN_INS_DIR)" ; \
		cd $(BLD_TOP); top=`pwd` ; cd /tmp ; unzip -o $$top/releases/$(BLD_PRODUCT)/$$name ; \
		name="${BLD_PRODUCT}-${BLD_VERSION}-${BLD_NUMBER}-${BLD_HOST_OS}-${BLD_HOST_CPU}.exe" ; \
		cp $$top/package/WIN/unattended.ans /tmp ; \
		echo "Dir=$(WIN_INS_DIR)" >>/tmp/unattended.ans ; \
		$$name /loadinf=/tmp/unattended.ans /silent ; \
	else \
		name="$(BASE_NAME).tar.tar.gz" ; \
		cd $(BLD_TOP); top=`pwd` ; cd /tmp ; tar xvfz $$top/releases/$$name ; \
		priv "$(BLD_PRODUCT)_HEADLESS=1 ./install" ; \
	fi

uninstall-package: prep
	if [ $(BLD_HOST_OS) = WIN ] ; then \
		if [ ! -x "$(WIN_INS_DIR)/unins000.exe" ] ; then \
			echo "Can't find $(WIN_INS_DIR)/unins000.exe to uninstall" ; \
			exit 255 ; \
		fi ; \
		"$(WIN_INS_DIR)/unins000.exe" /silent ; \
	else \
		name="$(BASE_NAME).tar.tar.gz" ; \
		cd $(BLD_TOP); top=`pwd` ; cd /tmp ; tar xvfz $$top/releases/$(BLD_PRODUCT)/$$name ; \
		priv "$(BLD_PRODUCT)_HEADLESS=1 ./remove" ; \
	fi

install: install-binary
   
install-%: prep
	packs=$* ; [ "$$packs" = "" ] && packs="binary dev" ; \
	[ "$$packs" = "all" ] && packs="binary dev" ; [ "$$packs" = "src" ] && packs="source" ; \
	[ "$$packs" != "$${packs/binary/}" ] && BROWSER=--browser ; \
	priv OPTIONS=$(OPTIONS) TRACE=$(TRACE) $(BLD_TOP)/build/bin/makeInstall $(BROWSER) --root=$(ROOT_DIR) --install "$$packs"

uninstall: uninstall-binary
   
uninstall-%: prep
	packs=$* ; [ "$$packs" = "" ] && packs="binary dev" ; \
	[ "$$packs" = "all" ] && packs="binary dev" ; [ "$$packs" = "src" ] && packs="source" ; \
	priv OPTIONS=$(OPTIONS) TRACE=$(TRACE) $(BLD_TOP)/build/bin/makeInstall --root=$(ROOT_DIR) --remove "$$packs"
	
checkInstalled:
	( \
		for d in /etc /usr/src /usr/share /usr/share/doc /usr/lib /usr/lib/$(BLD_PRODUCT) /usr/include \
			/usr/local/bin /usr/local/bin/$(BLD_PRODUCT) /usr/bin /usr/bin/$(BLD_PRODUCT) \
			/usr/include/$(BLD_PRODUCT) /var/log /var/www ; \
		do \
			if [ "`echo $$d/$(BLD_PRODUCT)*`" != $$d/$(BLD_PRODUCT)'*' ] ; then \
				eval echo "$$d/$(BLD_PRODUCT)*" ; \
				continue ; \
			fi ; \
			if [ -x "$$d/$(BLD_PRODUCT)" ] ; then \
				echo "$$d/$(BLD_PRODUCT)" ; \
				continue ; \
			fi ; \
		done ; \
		for d in "$(BLD_CFG_PREFIX)" "$(BLD_DOC_PREFIX)" "$(BLD_INC_PREFIX)" "$(BLD_LIB_PREFIX)" "$(BLD_LOG_PREFIX)" \
			"$(BLD_SAM_PREFIX)" "$(BLD_SRC_PREFIX)" ; \
		do \
			[ -x "$$d" ] && echo "$$d" || true; \
		done ; \
	) | sort | uniq

prep:
	if [ ! -x $(BLD_TOOLS_DIR)/edep$(BLD_BUILD_EXE) -a "$(BUILDING_CROSS)" != 1 ] ; then \
		$(MAKE) -S --no-print-directory _RECURSIVE_=1 -C $(BLD_TOP)/build/src compile ; \
	fi

dependExtra:
	[ "$(shell echo *.sh)" != "*.sh" ] && chmod +x *.sh ; true

#
#   Local variables:
#   tab-width: 4
#   c-basic-offset: 4
#   End:
#   vim: sw=4 ts=4 noexpandtab
#
