ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)

#####################################
# Preset make macros go here
#####################################

EXTRA_SRCVPATH+=$(PRODUCT_ROOT)/src

EXTRA_INCVPATH+=$(PRODUCT_ROOT)/../..

# Use same flags from Jamfile to make a shared library
CCFLAGS += -DBOOST_SERIALIZATION_DYN_LINK=1

SRCS= basic_archive.cpp \
basic_iarchive.cpp \
basic_iserializer.cpp \
basic_oarchive.cpp \
basic_oserializer.cpp \
basic_pointer_iserializer.cpp \
basic_pointer_oserializer.cpp \
basic_serializer_map.cpp \
basic_text_iprimitive.cpp \
basic_text_oprimitive.cpp \
basic_xml_archive.cpp \
binary_iarchive.cpp \
binary_oarchive.cpp \
extended_type_info.cpp \
extended_type_info_typeid.cpp \
extended_type_info_no_rtti.cpp \
polymorphic_iarchive.cpp \
polymorphic_oarchive.cpp \
stl_port.cpp \
text_iarchive.cpp \
text_oarchive.cpp \
void_cast.cpp \
archive_exception.cpp \
xml_grammar.cpp \
xml_iarchive.cpp \
xml_oarchive.cpp \
xml_archive_exception.cpp \
shared_ptr_helper.cpp

include ../../../../rim_preset.mk

define PINFO
PINFO DESCRIPTION=Boost.Serialization library
endef

NAME=boost_serialization

include $(MKFILES_ROOT)/qtargets.mk

#####################################
# Post-set make macros go here
#####################################

include ../../../../rim_postset.mk
