ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)

#####################################
# Preset make macros go here
#####################################

EXTRA_SRCVPATH+=$(PRODUCT_ROOT)/src
EXTRA_SRCVPATH+=$(PRODUCT_ROOT)/src/gregorian
EXTRA_SRCVPATH+=$(PRODUCT_ROOT)/src/posix_time

EXTRA_INCVPATH+=$(PRODUCT_ROOT)/../..

CCFLAGS += -DDATE_TIME_INLINE

include ../../../../rim_preset.mk

define PINFO
PINFO DESCRIPTION=Boost.Date_Time library
endef

NAME=boost_date_time

include $(MKFILES_ROOT)/qtargets.mk

#####################################
# Post-set make macros go here
#####################################

include ../../../../rim_postset.mk

ifeq ($(filter so,$(VARIANT_LIST)),so)
    # Use same flags from Jamfile to make a shared library
    CCFLAGS += -DBOOST_DATE_TIME_DYN_LINK=1
endif
