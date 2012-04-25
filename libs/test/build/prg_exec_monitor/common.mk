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

SRCS=\
execution_monitor.cpp \
debug.cpp \
cpp_main.cpp

include ../../../../../rim_preset.mk

define PINFO
PINFO DESCRIPTION=Boost.Test PRG_EXEC_MON library
endef

NAME=boost_prg_exec_monitor

include $(MKFILES_ROOT)/qtargets.mk

#####################################
# Post-set make macros go here
#####################################

include ../../../../../rim_postset.mk
