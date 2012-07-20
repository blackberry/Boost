ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)

#####################################
# Preset make macros go here
#####################################

EXTRA_SRCVPATH+=$(PRODUCT_ROOT)/src

EXTRA_INCVPATH+=$(PRODUCT_ROOT)/../..

include ../../../../rim_preset.mk

define PINFO
PINFO DESCRIPTION=Boost.Program_options library
endef

NAME=boost_program_options

include $(MKFILES_ROOT)/qtargets.mk

#####################################
# Post-set make macros go here
#####################################

include ../../../../rim_postset.mk

ifeq ($(filter so,$(VARIANT_LIST)),so)
    # Use same flags from Jamfile to make a shared library
    CCFLAGS += -DBOOST_PROGRAM_OPTIONS_DYN_LINK=1 
endif
