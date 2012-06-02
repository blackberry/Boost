ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)

#####################################
# Preset make macros go here
#####################################

EXTRA_SRCVPATH+=$(PROJECT_ROOT)/

EXTRA_INCVPATH+=$(PRODUCT_ROOT)/../../..

EXTRA_LIBVPATH+=/home/chung/dev/boost/libs/regex/build/arm/a-le-v7-g
EXTRA_LIBVPATH+=/home/chung/dev/boost/libs/thread/build/arm/a-le-v7-g
EXTRA_LIBVPATH+=/home/chung/dev/boost/libs/system/build/arm/a-le-v7-g
EXTRA_LIBVPATH+=$(PRODUCT_ROOT)/recursive/arm/a-le-v7-g

# Use same flags from Jamfile to make a shared library
CCFLAGS += -DBOOST_REGEX_DYN_LINK=1
CCFLAGS += -DBOOST_HAS_ICU=1 
CCFLAGS += -DBOOST_ALL_NO_LIB=1
CCFLAGS += -Wextra
CCFLAGS += -Wshadow
CCFLAGS += -DU_USING_ICU_NAMESPACE=0
CCFLAGS += -DTEST_THREADS
CCFLAGS += -DBOOST_THREAD_POSIX 
CCFLAGS += -DBOOST_THREAD_USE_DLL=1
CCFLAGS += -DBOOST_REGEX_NON_RECURSIVE=1

# Check if the test still crashes with this defined
#CCFLAGS += -DBOOST_NO_EXCEPTIONS=1

LIBPREF_boost_regex_g = -Bstatic
LIBPOST_boost_regex_recursive_g= -Bdynamic

include ../../../../../rim_preset.mk

define PINFO
PINFO DESCRIPTION=Boost.Regex regex_regress_threaded test
endef
INSTALLDIR=usr/bin

NAME=regex_regress_threaded

include $(MKFILES_ROOT)/qtargets.mk

#####################################
# Post-set make macros go here
#####################################

include ../../../../../rim_postset.mk

# This allows for dynamic linking without static libraries being present
LIBS+=boost_regex_g
LIBS+=boost_thread_g
LIBS+=boost_system_g
LIBS+=boost_regex_recursive_g
LIBS+=icuuc
LIBS+=icui18n
LIBS+=icudata
LIBS+=m


