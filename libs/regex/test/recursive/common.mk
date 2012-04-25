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
CCFLAGS += -DU_USING_ICU_NAMESPACE=0
CCFLAGS += -DBOOST_REGEX_RECURSIVE=1
CCFLAGS += -DBOOST_HAS_ICU=1 
CCFLAGS += -DBOOST_ALL_NO_LIB=1 

SRCS= c_regex_traits.cpp \
cpp_regex_traits.cpp \
cregex.cpp \
fileiter.cpp \
icu.cpp \
instances.cpp \
posix_api.cpp \
regex.cpp \
regex_debug.cpp \
regex_raw_buffer.cpp \
regex_traits_defaults.cpp \
static_mutex.cpp \
w32_regex_traits.cpp \
wc_regex_traits.cpp \
wide_posix_api.cpp \
winstances.cpp  \
usinstances.cpp 

include ../../../../../rim_preset.mk

define PINFO
PINFO DESCRIPTION=Boost.Regex Recursive library
endef

NAME=boost_regex_recursive

include $(MKFILES_ROOT)/qtargets.mk

#####################################
# Post-set make macros go here
#####################################

include ../../../../../rim_postset.mk
