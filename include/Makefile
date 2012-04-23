#*****************************************************************************
# This Makefile performs the common hinstall step that installs all of the
# Boost headers once, for all variants and all separately-compiled libraries.
#
# This is done because the individual libraries do not have their own totally
# independent set of headers.  For the most part they rely on the full package
# of Boost headers, and so we simply copy them into the install location once.
#
#=============================================================================
# Include the normal QNX rules

ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)

#=============================================================================
# Rules for installing headers
#
# To do this, we cheat a small amount, but at least our cheating is contained
# within this section of this file.

# Targets we simply ignore
first all install clean:
.PHONY: first all install clean

# Include the macros so we can figure out where to install.  Any CPU value
# will do, so just pretend it is arm.  Ick.
CPU=arm
include $(MKFILES_ROOT)/qmacros.mk

# Unconditionally copy all the headers over.  Don't expect anything else to be
# in the boost/ header directory in the install root.
.PHONY: hinstall
hinstall:
#	$(RM_HOST) -rf $(INSTALL_ROOT_HDR)/boost
#	$(RM_HOST) -rf $(QNX_TARGET)/boost
#	$(CP_HOST) -r boost $(INSTALL_ROOT_HDR)/boost
#	$(warning INSTALL_ROOT=${INSTALL_ROOT})
	$(RM_HOST) -rf $(INSTALL_ROOT_nto)/usr/include/boost
	sh -x ./cp-headers.sh $(INSTALL_ROOT_nto) 

.PHONY: install
install: hinstall

#=============================================================================
# For debugging this Makefile

.PHONY: local_debug
local_debug:
	#INSTALL_ROOT_HDR=$(INSTALL_ROOT_HDR)

#*****************************************************************************
