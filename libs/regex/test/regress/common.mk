ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)

#####################################
# Preset make macros go here
#####################################

EXTRA_SRCVPATH+=$(PROJECT_ROOT)/

EXTRA_INCVPATH+=$(PRODUCT_ROOT)/../../..

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

# Use the QNX build system's $(VARIANT_LIST) to determine whether to use
# debugging libraries, etc.
ifeq ($(filter g,$(VARIANT_LIST)),g)
    LIBS+=boost_regex_g
    LIBS+=boost_thread_g
    LIBS+=boost_system_g
    LIBS+=boost_regex_recursive_g
    LIBPREF_boost_regex_g = -Bstatic
    LIBPOST_boost_regex_recursive_g = -Bdynamic
else
    # Non-debug build.
    LIBS+=boost_regex
    LIBS+=boost_thread
    LIBS+=boost_system
    LIBS+=boost_regex_recursive
    LIBPREF_boost_regex = -Bstatic
    LIBPOST_boost_regex_recursive = -Bdynamic
endif

# Adding to LIBS in this section allows for dynamic linking without static libraries being present
LIBS+=icuuc
LIBS+=icui18n
LIBS+=icudata
LIBS+=m

ifeq ($(CPU),arm)
    ifeq ($(filter g,$(VARIANT_LIST)),g)
        EXTRA_LIBVPATH+=$(PROJECT_ROOT)/../../build/$(CPU)/a-le-v7-g
        EXTRA_LIBVPATH+=$(PROJECT_ROOT)/../../../thread/build/$(CPU)/a-le-v7-g
        EXTRA_LIBVPATH+=$(PROJECT_ROOT)/../../../system/build/$(CPU)/a-le-v7-g
        EXTRA_LIBVPATH+=$(PRODUCT_ROOT)/recursive/$(CPU)/a-le-v7-g
    else
        # Non-debug build.
        EXTRA_LIBVPATH+=$(PROJECT_ROOT)/../../build/$(CPU)/a-le-v7
        EXTRA_LIBVPATH+=$(PROJECT_ROOT)/../../../thread/build/$(CPU)/a-le-v7
        EXTRA_LIBVPATH+=$(PROJECT_ROOT)/../../../system/build/$(CPU)/a-le-v7
        EXTRA_LIBVPATH+=$(PRODUCT_ROOT)/recursive/$(CPU)/a-le-v7
    endif
else
    ifeq ($(CPU),x86)
        ifeq ($(filter g,$(VARIANT_LIST)),g)
            EXTRA_LIBVPATH+=$(PROJECT_ROOT)/../../build/$(CPU)/a-g
            EXTRA_LIBVPATH+=$(PROJECT_ROOT)/../../../thread/build/$(CPU)/a-g
            EXTRA_LIBVPATH+=$(PROJECT_ROOT)/../../../system/build/$(CPU)/a-g
            EXTRA_LIBVPATH+=$(PRODUCT_ROOT)/recursive/$(CPU)/a-g
        else
            # Non-debug build.
            EXTRA_LIBVPATH+=$(PROJECT_ROOT)/../../build/$(CPU)/a
            EXTRA_LIBVPATH+=$(PROJECT_ROOT)/../../../thread/build/$(CPU)/a
            EXTRA_LIBVPATH+=$(PROJECT_ROOT)/../../../system/build/$(CPU)/a
            EXTRA_LIBVPATH+=$(PRODUCT_ROOT)/recursive/$(CPU)/a
        endif
    endif
endif

