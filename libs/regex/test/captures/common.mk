ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)

#####################################
# Preset make macros go here
#####################################

EXTRA_SRCVPATH+=$(PRODUCT_ROOT)/../src

EXTRA_INCVPATH+=$(PRODUCT_ROOT)/../../..

# Use same flags from Jamfile to make a shared library
CCFLAGS += -DBOOST_REGEX_DYN_LINK=1
CCFLAGS += -DBOOST_REGEX_MATCH_EXTRA=1
CCFLAGS += -DBOOST_ALL_NO_LIB=1
CCFLAGS += -DU_USING_ICU_NAMESPACE=0 
 
EXCLUDE_OBJS += \
  captures_test.o

include ../../../../../rim_preset.mk

define PINFO
PINFO DESCRIPTION=Boost.Regex library
endef

NAME=boost_regex_extra

include $(MKFILES_ROOT)/qtargets.mk

#####################################
# Post-set make macros go here
#####################################

include ../../../../../rim_postset.mk
