ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)

#####################################
# Preset make macros go here
#####################################

EXTRA_SRCVPATH+=$(PRODUCT_ROOT)/../src

EXTRA_INCVPATH+=$(PRODUCT_ROOT)/../../..

# Use same flags from Jamfile to make a static lib
CCFLAGS += -Wextra
CCFLAGS += -Wshadow
CCFLAGS += -DU_USING_ICU_NAMESPACE=0
CCFLAGS += -DBOOST_NO_EXCEPTIONS=1
CCFLAGS += -DBOOST_ALL_NO_LIB=1
CCFLAGS += -DBOOST_HAS_ICU=1 

include ../../../../../rim_preset.mk

define PINFO
PINFO DESCRIPTION=Boost.Regex NOEH library
endef

NAME=boost_regex_noeh

include $(MKFILES_ROOT)/qtargets.mk

#####################################
# Post-set make macros go here
#####################################

include ../../../../../rim_postset.mk
