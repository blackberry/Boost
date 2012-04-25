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
CCFLAGS += -DBOOST_TEST_DYN_LINK=1 

# Skip the files that are not part of the unit test framework
EXCLUDE_OBJS += \
  cpp_main.o \
  test_main.o

include ../../../../../rim_preset.mk

define PINFO
PINFO DESCRIPTION=Boost.Test library
endef

NAME=boost_test

include $(MKFILES_ROOT)/qtargets.mk

#####################################
# Post-set make macros go here
#####################################

include ../../../../../rim_postset.mk
