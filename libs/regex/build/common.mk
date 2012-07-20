ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)

#####################################
# Preset make macros go here
#####################################

EXTRA_SRCVPATH+=$(PRODUCT_ROOT)/src

EXTRA_INCVPATH+=$(PRODUCT_ROOT)/../..

CCFLAGS += -DBOOST_HAS_ICU=1 
CCFLAGS += -DBOOST_ALL_NO_LIB=1

include ../../../../rim_preset.mk

define PINFO
PINFO DESCRIPTION=Boost.Regex library
endef

NAME=boost_regex

include $(MKFILES_ROOT)/qtargets.mk

#####################################
# Post-set make macros go here
#####################################

include ../../../../rim_postset.mk

ifeq ($(filter so,$(VARIANT_LIST)),so)
    # Use same flags from Jamfile to make a shared library
    CCFLAGS += -DBOOST_REGEX_DYN_LINK=1
endif
