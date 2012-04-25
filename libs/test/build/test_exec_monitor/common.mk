ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)

#####################################
# Preset make macros go here
#####################################

EXTRA_SRCVPATH+=$(PRODUCT_ROOT)/../src

EXTRA_INCVPATH+=$(PRODUCT_ROOT)/../../..

# Use same flags from Jamfile
#CCFLAGS += -DBOOST_TEST_DYN_LINK=1 
CCFLAGS += -DBOOST_ALL_NO_LIB=1 

SRCS= compiler_log_formatter.cpp \
debug.cpp \
execution_monitor.cpp \
framework.cpp \
plain_report_formatter.cpp \
progress_monitor.cpp \
results_collector.cpp \
results_reporter.cpp \
test_main.cpp \
test_tools.cpp \
unit_test_log.cpp \
unit_test_main.cpp \
unit_test_monitor.cpp \
unit_test_parameters.cpp \
unit_test_suite.cpp \
xml_log_formatter.cpp \
xml_report_formatter.cpp

include ../../../../../rim_preset.mk

define PINFO
PINFO DESCRIPTION=Boost.Test Exec Monitor library
endef

NAME=boost_test_exec_monitor

include $(MKFILES_ROOT)/qtargets.mk

#####################################
# Post-set make macros go here
#####################################

include ../../../../../rim_postset.mk
