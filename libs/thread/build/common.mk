ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)

#####################################
# Preset make macros go here
#####################################

EXTRA_SRCVPATH+=$(PRODUCT_ROOT)/src
EXTRA_SRCVPATH+=$(PRODUCT_ROOT)/src/pthread

EXTRA_INCVPATH+=$(PRODUCT_ROOT)/../..

# Use same flags from Jamfile to make a shared library
CCFLAGS += -DBOOST_THREAD_BUILD_DLL
CCFLAGS += -DBOOST_THREAD_POSIX 
CCFLAGS += -DBOOST_ALL_DYN_LINK=1	

include ../../../../rim_preset.mk

define PINFO
PINFO DESCRIPTION=Boost.Thread library
endef

NAME=boost_thread

include $(MKFILES_ROOT)/qtargets.mk

#####################################
# Post-set make macros go here
#####################################

include ../../../../rim_postset.mk
