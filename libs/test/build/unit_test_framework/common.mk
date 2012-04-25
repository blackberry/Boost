ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)

#####################################
# Preset make macros go here
#####################################

EXTRA_SRCVPATH+=$(PRODUCT_ROOT)/../src

EXTRA_INCVPATH+=$(PRODUCT_ROOT)/../../..

SRCS=\
  compiler_log_formatter.cpp \
  debug.cpp \
  exception_safety.cpp \
  execution_monitor.cpp \
  framework.cpp \
  interaction_based.cpp \
  logged_expectations.cpp \
  plain_report_formatter.cpp \
  progress_monitor.cpp \
  results_collector.cpp \
  results_reporter.cpp \
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
PINFO DESCRIPTION=Boost.Test UTF library
endef

NAME=boost_unit_test_framework

include $(MKFILES_ROOT)/qtargets.mk

#####################################
# Post-set make macros go here
#####################################
# Need to check if it is a static or dynamic lib when setting flags
ifeq ($(filter a,$(VARIANT_LIST)),a)
    CCFLAGS += -DBOOST_ALL_NO_LIB=1 
else
    CCFLAGS += -DBOOST_TEST_DYN_LINK=1
endif

include ../../../../../rim_postset.mk
