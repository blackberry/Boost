# copyright John Maddock 2006
# Distributed under the Boost Software License, Version 1.0. 
# (See accompanying file LICENSE_1_0.txt or copy at 
# http://www.boost.org/LICENSE_1_0.txt.
#
# auto generated makefile for MSVC compiler
#
# usage:
# make
#   brings libraries up to date
# make install
#   brings libraries up to date and copies binaries to your VC6 /lib and /bin directories (recomended)
#

#
# path to ICU library installation goes here:
#
ICU_PATH=
#
# Add additional compiler options here:
#
CXXFLAGS=
#
# Add additional include directories here:
#
INCLUDES=
#
# add additional linker flags here:
#
XLFLAGS=
#
# add additional static-library creation flags here:
#
XSFLAGS=

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF "$(MSVCDIR)" == ""
MSVCDIR=$(VS100COMNTOOLS)..\..\VC
!ENDIF

!IF "$(MSVCDIR)" == ""
!ERROR Variable MSVCDIR not set.
!ENDIF

!IF "$(ICU_PATH)" == ""
ICU_COMPILE_OPTS=
ICU_LINK_OPTS=
!MESSAGE Building Boost.Regex without ICU / Unicode support:
!MESSAGE Hint: set ICU_PATH on the nmake command line to point 
!MESSAGE to your ICU installation if you have one.
!ELSE
ICU_COMPILE_OPTS= -DBOOST_HAS_ICU=1 -I"$(ICU_PATH)\include"
ICU_LINK_OPTS= /LIBPATH:"$(ICU_PATH)\lib" icuin.lib icuuc.lib
!MESSAGE Building Boost.Regex with ICU in $(ICU_PATH)
!ENDIF


ALL_HEADER= ../../../boost/regex/config.hpp ../../../boost/regex/icu.hpp ../../../boost/regex/pattern_except.hpp ../../../boost/regex/regex_traits.hpp ../../../boost/regex/user.hpp ../../../boost/regex/v4/basic_regex.hpp ../../../boost/regex/v4/basic_regex_creator.hpp ../../../boost/regex/v4/basic_regex_parser.hpp ../../../boost/regex/v4/c_regex_traits.hpp ../../../boost/regex/v4/char_regex_traits.hpp ../../../boost/regex/v4/cpp_regex_traits.hpp ../../../boost/regex/v4/cregex.hpp ../../../boost/regex/v4/error_type.hpp ../../../boost/regex/v4/fileiter.hpp ../../../boost/regex/v4/instances.hpp ../../../boost/regex/v4/iterator_category.hpp ../../../boost/regex/v4/iterator_traits.hpp ../../../boost/regex/v4/match_flags.hpp ../../../boost/regex/v4/match_results.hpp ../../../boost/regex/v4/mem_block_cache.hpp ../../../boost/regex/v4/perl_matcher.hpp ../../../boost/regex/v4/perl_matcher_common.hpp ../../../boost/regex/v4/perl_matcher_non_recursive.hpp ../../../boost/regex/v4/perl_matcher_recursive.hpp ../../../boost/regex/v4/primary_transform.hpp ../../../boost/regex/v4/protected_call.hpp ../../../boost/regex/v4/regbase.hpp ../../../boost/regex/v4/regex.hpp ../../../boost/regex/v4/regex_format.hpp ../../../boost/regex/v4/regex_fwd.hpp ../../../boost/regex/v4/regex_grep.hpp ../../../boost/regex/v4/regex_iterator.hpp ../../../boost/regex/v4/regex_match.hpp ../../../boost/regex/v4/regex_merge.hpp ../../../boost/regex/v4/regex_raw_buffer.hpp ../../../boost/regex/v4/regex_replace.hpp ../../../boost/regex/v4/regex_search.hpp ../../../boost/regex/v4/regex_split.hpp ../../../boost/regex/v4/regex_token_iterator.hpp ../../../boost/regex/v4/regex_traits.hpp ../../../boost/regex/v4/regex_traits_defaults.hpp ../../../boost/regex/v4/regex_workaround.hpp ../../../boost/regex/v4/states.hpp ../../../boost/regex/v4/sub_match.hpp ../../../boost/regex/v4/syntax_type.hpp ../../../boost/regex/v4/u32regex_iterator.hpp ../../../boost/regex/v4/u32regex_token_iterator.hpp ../../../boost/regex/v4/w32_regex_traits.hpp ../../../boost/regex/config/borland.hpp ../../../boost/regex/config/cwchar.hpp

all : main_dir libboost_regex-vc100-mt-s-1_52_dir ./vc100/libboost_regex-vc100-mt-s-1_52.lib libboost_regex-vc100-mt-sgd-1_52_dir ./vc100/libboost_regex-vc100-mt-sgd-1_52.lib boost_regex-vc100-mt-gd-1_52_dir ./vc100/boost_regex-vc100-mt-gd-1_52.lib boost_regex-vc100-mt-1_52_dir ./vc100/boost_regex-vc100-mt-1_52.lib libboost_regex-vc100-mt-1_52_dir ./vc100/libboost_regex-vc100-mt-1_52.lib libboost_regex-vc100-mt-gd-1_52_dir ./vc100/libboost_regex-vc100-mt-gd-1_52.lib

clean :  libboost_regex-vc100-mt-s-1_52_clean libboost_regex-vc100-mt-sgd-1_52_clean boost_regex-vc100-mt-gd-1_52_clean boost_regex-vc100-mt-1_52_clean libboost_regex-vc100-mt-1_52_clean libboost_regex-vc100-mt-gd-1_52_clean

install : all
	copy vc100\libboost_regex-vc100-mt-s-1_52.lib "$(MSVCDIR)\lib"
	copy vc100\libboost_regex-vc100-mt-sgd-1_52.lib "$(MSVCDIR)\lib"
	copy vc100\boost_regex-vc100-mt-gd-1_52.lib "$(MSVCDIR)\lib"
	copy vc100\boost_regex-vc100-mt-gd-1_52.dll "$(MSVCDIR)\bin"
	copy vc100\boost_regex-vc100-mt-1_52.lib "$(MSVCDIR)\lib"
	copy vc100\boost_regex-vc100-mt-1_52.dll "$(MSVCDIR)\bin"
	copy vc100\libboost_regex-vc100-mt-1_52.lib "$(MSVCDIR)\lib"
	copy vc100\libboost_regex-vc100-mt-gd-1_52.lib "$(MSVCDIR)\lib"
	copy vc100\libboost_regex-vc100-mt-gd-1_52.pdb "$(MSVCDIR)\lib"

main_dir :
	@if not exist "vc100\$(NULL)" mkdir vc100


########################################################
#
# section for libboost_regex-vc100-mt-s-1_52.lib
#
########################################################
vc100/libboost_regex-vc100-mt-s-1_52/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /EHsc /O2  /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /Zc:wchar_t /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-s-1_52/ -Fdvc100/libboost_regex-vc100-mt-s-1_52.pdb ../src/c_regex_traits.cpp

vc100/libboost_regex-vc100-mt-s-1_52/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /EHsc /O2  /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /Zc:wchar_t /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-s-1_52/ -Fdvc100/libboost_regex-vc100-mt-s-1_52.pdb ../src/cpp_regex_traits.cpp

vc100/libboost_regex-vc100-mt-s-1_52/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /EHsc /O2  /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /Zc:wchar_t /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-s-1_52/ -Fdvc100/libboost_regex-vc100-mt-s-1_52.pdb ../src/cregex.cpp

vc100/libboost_regex-vc100-mt-s-1_52/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /EHsc /O2  /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /Zc:wchar_t /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-s-1_52/ -Fdvc100/libboost_regex-vc100-mt-s-1_52.pdb ../src/fileiter.cpp

vc100/libboost_regex-vc100-mt-s-1_52/icu.obj: ../src/icu.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /EHsc /O2  /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /Zc:wchar_t /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-s-1_52/ -Fdvc100/libboost_regex-vc100-mt-s-1_52.pdb ../src/icu.cpp

vc100/libboost_regex-vc100-mt-s-1_52/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /EHsc /O2  /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /Zc:wchar_t /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-s-1_52/ -Fdvc100/libboost_regex-vc100-mt-s-1_52.pdb ../src/instances.cpp

vc100/libboost_regex-vc100-mt-s-1_52/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /EHsc /O2  /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /Zc:wchar_t /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-s-1_52/ -Fdvc100/libboost_regex-vc100-mt-s-1_52.pdb ../src/posix_api.cpp

vc100/libboost_regex-vc100-mt-s-1_52/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /EHsc /O2  /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /Zc:wchar_t /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-s-1_52/ -Fdvc100/libboost_regex-vc100-mt-s-1_52.pdb ../src/regex.cpp

vc100/libboost_regex-vc100-mt-s-1_52/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /EHsc /O2  /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /Zc:wchar_t /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-s-1_52/ -Fdvc100/libboost_regex-vc100-mt-s-1_52.pdb ../src/regex_debug.cpp

vc100/libboost_regex-vc100-mt-s-1_52/regex_raw_buffer.obj: ../src/regex_raw_buffer.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /EHsc /O2  /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /Zc:wchar_t /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-s-1_52/ -Fdvc100/libboost_regex-vc100-mt-s-1_52.pdb ../src/regex_raw_buffer.cpp

vc100/libboost_regex-vc100-mt-s-1_52/regex_traits_defaults.obj: ../src/regex_traits_defaults.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /EHsc /O2  /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /Zc:wchar_t /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-s-1_52/ -Fdvc100/libboost_regex-vc100-mt-s-1_52.pdb ../src/regex_traits_defaults.cpp

vc100/libboost_regex-vc100-mt-s-1_52/static_mutex.obj: ../src/static_mutex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /EHsc /O2  /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /Zc:wchar_t /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-s-1_52/ -Fdvc100/libboost_regex-vc100-mt-s-1_52.pdb ../src/static_mutex.cpp

vc100/libboost_regex-vc100-mt-s-1_52/usinstances.obj: ../src/usinstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /EHsc /O2  /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /Zc:wchar_t /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-s-1_52/ -Fdvc100/libboost_regex-vc100-mt-s-1_52.pdb ../src/usinstances.cpp

vc100/libboost_regex-vc100-mt-s-1_52/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /EHsc /O2  /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /Zc:wchar_t /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-s-1_52/ -Fdvc100/libboost_regex-vc100-mt-s-1_52.pdb ../src/w32_regex_traits.cpp

vc100/libboost_regex-vc100-mt-s-1_52/wc_regex_traits.obj: ../src/wc_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /EHsc /O2  /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /Zc:wchar_t /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-s-1_52/ -Fdvc100/libboost_regex-vc100-mt-s-1_52.pdb ../src/wc_regex_traits.cpp

vc100/libboost_regex-vc100-mt-s-1_52/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /EHsc /O2  /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /Zc:wchar_t /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-s-1_52/ -Fdvc100/libboost_regex-vc100-mt-s-1_52.pdb ../src/wide_posix_api.cpp

vc100/libboost_regex-vc100-mt-s-1_52/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /EHsc /O2  /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /Zc:wchar_t /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-s-1_52/ -Fdvc100/libboost_regex-vc100-mt-s-1_52.pdb ../src/winstances.cpp

libboost_regex-vc100-mt-s-1_52_dir :
	@if not exist "vc100\libboost_regex-vc100-mt-s-1_52\$(NULL)" mkdir vc100\libboost_regex-vc100-mt-s-1_52

libboost_regex-vc100-mt-s-1_52_clean :
	del vc100\libboost_regex-vc100-mt-s-1_52\*.obj
	del vc100\libboost_regex-vc100-mt-s-1_52\*.idb
	del vc100\libboost_regex-vc100-mt-s-1_52\*.exp
	del vc100\libboost_regex-vc100-mt-s-1_52\*.pch

./vc100/libboost_regex-vc100-mt-s-1_52.lib : vc100/libboost_regex-vc100-mt-s-1_52/c_regex_traits.obj vc100/libboost_regex-vc100-mt-s-1_52/cpp_regex_traits.obj vc100/libboost_regex-vc100-mt-s-1_52/cregex.obj vc100/libboost_regex-vc100-mt-s-1_52/fileiter.obj vc100/libboost_regex-vc100-mt-s-1_52/icu.obj vc100/libboost_regex-vc100-mt-s-1_52/instances.obj vc100/libboost_regex-vc100-mt-s-1_52/posix_api.obj vc100/libboost_regex-vc100-mt-s-1_52/regex.obj vc100/libboost_regex-vc100-mt-s-1_52/regex_debug.obj vc100/libboost_regex-vc100-mt-s-1_52/regex_raw_buffer.obj vc100/libboost_regex-vc100-mt-s-1_52/regex_traits_defaults.obj vc100/libboost_regex-vc100-mt-s-1_52/static_mutex.obj vc100/libboost_regex-vc100-mt-s-1_52/usinstances.obj vc100/libboost_regex-vc100-mt-s-1_52/w32_regex_traits.obj vc100/libboost_regex-vc100-mt-s-1_52/wc_regex_traits.obj vc100/libboost_regex-vc100-mt-s-1_52/wide_posix_api.obj vc100/libboost_regex-vc100-mt-s-1_52/winstances.obj
	link -lib /nologo /out:vc100/libboost_regex-vc100-mt-s-1_52.lib $(XSFLAGS)  vc100/libboost_regex-vc100-mt-s-1_52/c_regex_traits.obj vc100/libboost_regex-vc100-mt-s-1_52/cpp_regex_traits.obj vc100/libboost_regex-vc100-mt-s-1_52/cregex.obj vc100/libboost_regex-vc100-mt-s-1_52/fileiter.obj vc100/libboost_regex-vc100-mt-s-1_52/icu.obj vc100/libboost_regex-vc100-mt-s-1_52/instances.obj vc100/libboost_regex-vc100-mt-s-1_52/posix_api.obj vc100/libboost_regex-vc100-mt-s-1_52/regex.obj vc100/libboost_regex-vc100-mt-s-1_52/regex_debug.obj vc100/libboost_regex-vc100-mt-s-1_52/regex_raw_buffer.obj vc100/libboost_regex-vc100-mt-s-1_52/regex_traits_defaults.obj vc100/libboost_regex-vc100-mt-s-1_52/static_mutex.obj vc100/libboost_regex-vc100-mt-s-1_52/usinstances.obj vc100/libboost_regex-vc100-mt-s-1_52/w32_regex_traits.obj vc100/libboost_regex-vc100-mt-s-1_52/wc_regex_traits.obj vc100/libboost_regex-vc100-mt-s-1_52/wide_posix_api.obj vc100/libboost_regex-vc100-mt-s-1_52/winstances.obj

########################################################
#
# section for libboost_regex-vc100-mt-sgd-1_52.lib
#
########################################################
vc100/libboost_regex-vc100-mt-sgd-1_52/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /EHsc /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /EHsc /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-sgd-1_52/ -Fdvc100/libboost_regex-vc100-mt-sgd-1_52.pdb ../src/c_regex_traits.cpp

vc100/libboost_regex-vc100-mt-sgd-1_52/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /EHsc /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /EHsc /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-sgd-1_52/ -Fdvc100/libboost_regex-vc100-mt-sgd-1_52.pdb ../src/cpp_regex_traits.cpp

vc100/libboost_regex-vc100-mt-sgd-1_52/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /EHsc /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /EHsc /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-sgd-1_52/ -Fdvc100/libboost_regex-vc100-mt-sgd-1_52.pdb ../src/cregex.cpp

vc100/libboost_regex-vc100-mt-sgd-1_52/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /EHsc /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /EHsc /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-sgd-1_52/ -Fdvc100/libboost_regex-vc100-mt-sgd-1_52.pdb ../src/fileiter.cpp

vc100/libboost_regex-vc100-mt-sgd-1_52/icu.obj: ../src/icu.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /EHsc /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /EHsc /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-sgd-1_52/ -Fdvc100/libboost_regex-vc100-mt-sgd-1_52.pdb ../src/icu.cpp

vc100/libboost_regex-vc100-mt-sgd-1_52/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /EHsc /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /EHsc /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-sgd-1_52/ -Fdvc100/libboost_regex-vc100-mt-sgd-1_52.pdb ../src/instances.cpp

vc100/libboost_regex-vc100-mt-sgd-1_52/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /EHsc /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /EHsc /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-sgd-1_52/ -Fdvc100/libboost_regex-vc100-mt-sgd-1_52.pdb ../src/posix_api.cpp

vc100/libboost_regex-vc100-mt-sgd-1_52/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /EHsc /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /EHsc /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-sgd-1_52/ -Fdvc100/libboost_regex-vc100-mt-sgd-1_52.pdb ../src/regex.cpp

vc100/libboost_regex-vc100-mt-sgd-1_52/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /EHsc /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /EHsc /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-sgd-1_52/ -Fdvc100/libboost_regex-vc100-mt-sgd-1_52.pdb ../src/regex_debug.cpp

vc100/libboost_regex-vc100-mt-sgd-1_52/regex_raw_buffer.obj: ../src/regex_raw_buffer.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /EHsc /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /EHsc /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-sgd-1_52/ -Fdvc100/libboost_regex-vc100-mt-sgd-1_52.pdb ../src/regex_raw_buffer.cpp

vc100/libboost_regex-vc100-mt-sgd-1_52/regex_traits_defaults.obj: ../src/regex_traits_defaults.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /EHsc /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /EHsc /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-sgd-1_52/ -Fdvc100/libboost_regex-vc100-mt-sgd-1_52.pdb ../src/regex_traits_defaults.cpp

vc100/libboost_regex-vc100-mt-sgd-1_52/static_mutex.obj: ../src/static_mutex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /EHsc /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /EHsc /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-sgd-1_52/ -Fdvc100/libboost_regex-vc100-mt-sgd-1_52.pdb ../src/static_mutex.cpp

vc100/libboost_regex-vc100-mt-sgd-1_52/usinstances.obj: ../src/usinstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /EHsc /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /EHsc /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-sgd-1_52/ -Fdvc100/libboost_regex-vc100-mt-sgd-1_52.pdb ../src/usinstances.cpp

vc100/libboost_regex-vc100-mt-sgd-1_52/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /EHsc /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /EHsc /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-sgd-1_52/ -Fdvc100/libboost_regex-vc100-mt-sgd-1_52.pdb ../src/w32_regex_traits.cpp

vc100/libboost_regex-vc100-mt-sgd-1_52/wc_regex_traits.obj: ../src/wc_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /EHsc /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /EHsc /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-sgd-1_52/ -Fdvc100/libboost_regex-vc100-mt-sgd-1_52.pdb ../src/wc_regex_traits.cpp

vc100/libboost_regex-vc100-mt-sgd-1_52/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /EHsc /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /EHsc /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-sgd-1_52/ -Fdvc100/libboost_regex-vc100-mt-sgd-1_52.pdb ../src/wide_posix_api.cpp

vc100/libboost_regex-vc100-mt-sgd-1_52/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /EHsc /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /EHsc /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-sgd-1_52/ -Fdvc100/libboost_regex-vc100-mt-sgd-1_52.pdb ../src/winstances.cpp

libboost_regex-vc100-mt-sgd-1_52_dir :
	@if not exist "vc100\libboost_regex-vc100-mt-sgd-1_52\$(NULL)" mkdir vc100\libboost_regex-vc100-mt-sgd-1_52

libboost_regex-vc100-mt-sgd-1_52_clean :
	del vc100\libboost_regex-vc100-mt-sgd-1_52\*.obj
	del vc100\libboost_regex-vc100-mt-sgd-1_52\*.idb
	del vc100\libboost_regex-vc100-mt-sgd-1_52\*.exp
	del vc100\libboost_regex-vc100-mt-sgd-1_52\*.pch

./vc100/libboost_regex-vc100-mt-sgd-1_52.lib : vc100/libboost_regex-vc100-mt-sgd-1_52/c_regex_traits.obj vc100/libboost_regex-vc100-mt-sgd-1_52/cpp_regex_traits.obj vc100/libboost_regex-vc100-mt-sgd-1_52/cregex.obj vc100/libboost_regex-vc100-mt-sgd-1_52/fileiter.obj vc100/libboost_regex-vc100-mt-sgd-1_52/icu.obj vc100/libboost_regex-vc100-mt-sgd-1_52/instances.obj vc100/libboost_regex-vc100-mt-sgd-1_52/posix_api.obj vc100/libboost_regex-vc100-mt-sgd-1_52/regex.obj vc100/libboost_regex-vc100-mt-sgd-1_52/regex_debug.obj vc100/libboost_regex-vc100-mt-sgd-1_52/regex_raw_buffer.obj vc100/libboost_regex-vc100-mt-sgd-1_52/regex_traits_defaults.obj vc100/libboost_regex-vc100-mt-sgd-1_52/static_mutex.obj vc100/libboost_regex-vc100-mt-sgd-1_52/usinstances.obj vc100/libboost_regex-vc100-mt-sgd-1_52/w32_regex_traits.obj vc100/libboost_regex-vc100-mt-sgd-1_52/wc_regex_traits.obj vc100/libboost_regex-vc100-mt-sgd-1_52/wide_posix_api.obj vc100/libboost_regex-vc100-mt-sgd-1_52/winstances.obj
	link -lib /nologo /out:vc100/libboost_regex-vc100-mt-sgd-1_52.lib $(XSFLAGS)  vc100/libboost_regex-vc100-mt-sgd-1_52/c_regex_traits.obj vc100/libboost_regex-vc100-mt-sgd-1_52/cpp_regex_traits.obj vc100/libboost_regex-vc100-mt-sgd-1_52/cregex.obj vc100/libboost_regex-vc100-mt-sgd-1_52/fileiter.obj vc100/libboost_regex-vc100-mt-sgd-1_52/icu.obj vc100/libboost_regex-vc100-mt-sgd-1_52/instances.obj vc100/libboost_regex-vc100-mt-sgd-1_52/posix_api.obj vc100/libboost_regex-vc100-mt-sgd-1_52/regex.obj vc100/libboost_regex-vc100-mt-sgd-1_52/regex_debug.obj vc100/libboost_regex-vc100-mt-sgd-1_52/regex_raw_buffer.obj vc100/libboost_regex-vc100-mt-sgd-1_52/regex_traits_defaults.obj vc100/libboost_regex-vc100-mt-sgd-1_52/static_mutex.obj vc100/libboost_regex-vc100-mt-sgd-1_52/usinstances.obj vc100/libboost_regex-vc100-mt-sgd-1_52/w32_regex_traits.obj vc100/libboost_regex-vc100-mt-sgd-1_52/wc_regex_traits.obj vc100/libboost_regex-vc100-mt-sgd-1_52/wide_posix_api.obj vc100/libboost_regex-vc100-mt-sgd-1_52/winstances.obj

########################################################
#
# section for boost_regex-vc100-mt-gd-1_52.lib
#
########################################################
vc100/boost_regex-vc100-mt-gd-1_52/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /EHsc /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /EHsc /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/boost_regex-vc100-mt-gd-1_52/ -Fdvc100/boost_regex-vc100-mt-gd-1_52.pdb ../src/c_regex_traits.cpp

vc100/boost_regex-vc100-mt-gd-1_52/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /EHsc /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /EHsc /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/boost_regex-vc100-mt-gd-1_52/ -Fdvc100/boost_regex-vc100-mt-gd-1_52.pdb ../src/cpp_regex_traits.cpp

vc100/boost_regex-vc100-mt-gd-1_52/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /EHsc /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /EHsc /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/boost_regex-vc100-mt-gd-1_52/ -Fdvc100/boost_regex-vc100-mt-gd-1_52.pdb ../src/cregex.cpp

vc100/boost_regex-vc100-mt-gd-1_52/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /EHsc /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /EHsc /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/boost_regex-vc100-mt-gd-1_52/ -Fdvc100/boost_regex-vc100-mt-gd-1_52.pdb ../src/fileiter.cpp

vc100/boost_regex-vc100-mt-gd-1_52/icu.obj: ../src/icu.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /EHsc /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /EHsc /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/boost_regex-vc100-mt-gd-1_52/ -Fdvc100/boost_regex-vc100-mt-gd-1_52.pdb ../src/icu.cpp

vc100/boost_regex-vc100-mt-gd-1_52/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /EHsc /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /EHsc /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/boost_regex-vc100-mt-gd-1_52/ -Fdvc100/boost_regex-vc100-mt-gd-1_52.pdb ../src/instances.cpp

vc100/boost_regex-vc100-mt-gd-1_52/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /EHsc /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /EHsc /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/boost_regex-vc100-mt-gd-1_52/ -Fdvc100/boost_regex-vc100-mt-gd-1_52.pdb ../src/posix_api.cpp

vc100/boost_regex-vc100-mt-gd-1_52/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /EHsc /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /EHsc /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/boost_regex-vc100-mt-gd-1_52/ -Fdvc100/boost_regex-vc100-mt-gd-1_52.pdb ../src/regex.cpp

vc100/boost_regex-vc100-mt-gd-1_52/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /EHsc /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /EHsc /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/boost_regex-vc100-mt-gd-1_52/ -Fdvc100/boost_regex-vc100-mt-gd-1_52.pdb ../src/regex_debug.cpp

vc100/boost_regex-vc100-mt-gd-1_52/regex_raw_buffer.obj: ../src/regex_raw_buffer.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /EHsc /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /EHsc /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/boost_regex-vc100-mt-gd-1_52/ -Fdvc100/boost_regex-vc100-mt-gd-1_52.pdb ../src/regex_raw_buffer.cpp

vc100/boost_regex-vc100-mt-gd-1_52/regex_traits_defaults.obj: ../src/regex_traits_defaults.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /EHsc /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /EHsc /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/boost_regex-vc100-mt-gd-1_52/ -Fdvc100/boost_regex-vc100-mt-gd-1_52.pdb ../src/regex_traits_defaults.cpp

vc100/boost_regex-vc100-mt-gd-1_52/static_mutex.obj: ../src/static_mutex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /EHsc /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /EHsc /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/boost_regex-vc100-mt-gd-1_52/ -Fdvc100/boost_regex-vc100-mt-gd-1_52.pdb ../src/static_mutex.cpp

vc100/boost_regex-vc100-mt-gd-1_52/usinstances.obj: ../src/usinstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /EHsc /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /EHsc /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/boost_regex-vc100-mt-gd-1_52/ -Fdvc100/boost_regex-vc100-mt-gd-1_52.pdb ../src/usinstances.cpp

vc100/boost_regex-vc100-mt-gd-1_52/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /EHsc /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /EHsc /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/boost_regex-vc100-mt-gd-1_52/ -Fdvc100/boost_regex-vc100-mt-gd-1_52.pdb ../src/w32_regex_traits.cpp

vc100/boost_regex-vc100-mt-gd-1_52/wc_regex_traits.obj: ../src/wc_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /EHsc /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /EHsc /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/boost_regex-vc100-mt-gd-1_52/ -Fdvc100/boost_regex-vc100-mt-gd-1_52.pdb ../src/wc_regex_traits.cpp

vc100/boost_regex-vc100-mt-gd-1_52/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /EHsc /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /EHsc /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/boost_regex-vc100-mt-gd-1_52/ -Fdvc100/boost_regex-vc100-mt-gd-1_52.pdb ../src/wide_posix_api.cpp

vc100/boost_regex-vc100-mt-gd-1_52/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /EHsc /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /EHsc /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/boost_regex-vc100-mt-gd-1_52/ -Fdvc100/boost_regex-vc100-mt-gd-1_52.pdb ../src/winstances.cpp

boost_regex-vc100-mt-gd-1_52_dir :
	@if not exist "vc100\boost_regex-vc100-mt-gd-1_52\$(NULL)" mkdir vc100\boost_regex-vc100-mt-gd-1_52

boost_regex-vc100-mt-gd-1_52_clean :
	del vc100\boost_regex-vc100-mt-gd-1_52\*.obj
	del vc100\boost_regex-vc100-mt-gd-1_52\*.idb
	del vc100\boost_regex-vc100-mt-gd-1_52\*.exp
	del vc100\boost_regex-vc100-mt-gd-1_52\*.pch

./vc100/boost_regex-vc100-mt-gd-1_52.lib : vc100/boost_regex-vc100-mt-gd-1_52/c_regex_traits.obj vc100/boost_regex-vc100-mt-gd-1_52/cpp_regex_traits.obj vc100/boost_regex-vc100-mt-gd-1_52/cregex.obj vc100/boost_regex-vc100-mt-gd-1_52/fileiter.obj vc100/boost_regex-vc100-mt-gd-1_52/icu.obj vc100/boost_regex-vc100-mt-gd-1_52/instances.obj vc100/boost_regex-vc100-mt-gd-1_52/posix_api.obj vc100/boost_regex-vc100-mt-gd-1_52/regex.obj vc100/boost_regex-vc100-mt-gd-1_52/regex_debug.obj vc100/boost_regex-vc100-mt-gd-1_52/regex_raw_buffer.obj vc100/boost_regex-vc100-mt-gd-1_52/regex_traits_defaults.obj vc100/boost_regex-vc100-mt-gd-1_52/static_mutex.obj vc100/boost_regex-vc100-mt-gd-1_52/usinstances.obj vc100/boost_regex-vc100-mt-gd-1_52/w32_regex_traits.obj vc100/boost_regex-vc100-mt-gd-1_52/wc_regex_traits.obj vc100/boost_regex-vc100-mt-gd-1_52/wide_posix_api.obj vc100/boost_regex-vc100-mt-gd-1_52/winstances.obj
	link kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /dll /incremental:yes /pdb:"vc100/boost_regex-vc100-mt-gd-1_52.pdb" /debug /machine:I386 /out:"vc100/boost_regex-vc100-mt-gd-1_52.dll" /implib:"vc100/boost_regex-vc100-mt-gd-1_52.lib" /LIBPATH:"$(STLPORT_PATH)\lib" $(XLFLAGS) $(ICU_LINK_OPTS)  vc100/boost_regex-vc100-mt-gd-1_52/c_regex_traits.obj vc100/boost_regex-vc100-mt-gd-1_52/cpp_regex_traits.obj vc100/boost_regex-vc100-mt-gd-1_52/cregex.obj vc100/boost_regex-vc100-mt-gd-1_52/fileiter.obj vc100/boost_regex-vc100-mt-gd-1_52/icu.obj vc100/boost_regex-vc100-mt-gd-1_52/instances.obj vc100/boost_regex-vc100-mt-gd-1_52/posix_api.obj vc100/boost_regex-vc100-mt-gd-1_52/regex.obj vc100/boost_regex-vc100-mt-gd-1_52/regex_debug.obj vc100/boost_regex-vc100-mt-gd-1_52/regex_raw_buffer.obj vc100/boost_regex-vc100-mt-gd-1_52/regex_traits_defaults.obj vc100/boost_regex-vc100-mt-gd-1_52/static_mutex.obj vc100/boost_regex-vc100-mt-gd-1_52/usinstances.obj vc100/boost_regex-vc100-mt-gd-1_52/w32_regex_traits.obj vc100/boost_regex-vc100-mt-gd-1_52/wc_regex_traits.obj vc100/boost_regex-vc100-mt-gd-1_52/wide_posix_api.obj vc100/boost_regex-vc100-mt-gd-1_52/winstances.obj

########################################################
#
# section for boost_regex-vc100-mt-1_52.lib
#
########################################################
vc100/boost_regex-vc100-mt-1_52/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /EHsc /O2  /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /Zc:wchar_t /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/boost_regex-vc100-mt-1_52/ -Fdvc100/boost_regex-vc100-mt-1_52.pdb ../src/c_regex_traits.cpp

vc100/boost_regex-vc100-mt-1_52/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /EHsc /O2  /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /Zc:wchar_t /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/boost_regex-vc100-mt-1_52/ -Fdvc100/boost_regex-vc100-mt-1_52.pdb ../src/cpp_regex_traits.cpp

vc100/boost_regex-vc100-mt-1_52/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /EHsc /O2  /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /Zc:wchar_t /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/boost_regex-vc100-mt-1_52/ -Fdvc100/boost_regex-vc100-mt-1_52.pdb ../src/cregex.cpp

vc100/boost_regex-vc100-mt-1_52/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /EHsc /O2  /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /Zc:wchar_t /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/boost_regex-vc100-mt-1_52/ -Fdvc100/boost_regex-vc100-mt-1_52.pdb ../src/fileiter.cpp

vc100/boost_regex-vc100-mt-1_52/icu.obj: ../src/icu.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /EHsc /O2  /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /Zc:wchar_t /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/boost_regex-vc100-mt-1_52/ -Fdvc100/boost_regex-vc100-mt-1_52.pdb ../src/icu.cpp

vc100/boost_regex-vc100-mt-1_52/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /EHsc /O2  /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /Zc:wchar_t /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/boost_regex-vc100-mt-1_52/ -Fdvc100/boost_regex-vc100-mt-1_52.pdb ../src/instances.cpp

vc100/boost_regex-vc100-mt-1_52/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /EHsc /O2  /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /Zc:wchar_t /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/boost_regex-vc100-mt-1_52/ -Fdvc100/boost_regex-vc100-mt-1_52.pdb ../src/posix_api.cpp

vc100/boost_regex-vc100-mt-1_52/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /EHsc /O2  /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /Zc:wchar_t /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/boost_regex-vc100-mt-1_52/ -Fdvc100/boost_regex-vc100-mt-1_52.pdb ../src/regex.cpp

vc100/boost_regex-vc100-mt-1_52/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /EHsc /O2  /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /Zc:wchar_t /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/boost_regex-vc100-mt-1_52/ -Fdvc100/boost_regex-vc100-mt-1_52.pdb ../src/regex_debug.cpp

vc100/boost_regex-vc100-mt-1_52/regex_raw_buffer.obj: ../src/regex_raw_buffer.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /EHsc /O2  /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /Zc:wchar_t /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/boost_regex-vc100-mt-1_52/ -Fdvc100/boost_regex-vc100-mt-1_52.pdb ../src/regex_raw_buffer.cpp

vc100/boost_regex-vc100-mt-1_52/regex_traits_defaults.obj: ../src/regex_traits_defaults.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /EHsc /O2  /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /Zc:wchar_t /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/boost_regex-vc100-mt-1_52/ -Fdvc100/boost_regex-vc100-mt-1_52.pdb ../src/regex_traits_defaults.cpp

vc100/boost_regex-vc100-mt-1_52/static_mutex.obj: ../src/static_mutex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /EHsc /O2  /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /Zc:wchar_t /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/boost_regex-vc100-mt-1_52/ -Fdvc100/boost_regex-vc100-mt-1_52.pdb ../src/static_mutex.cpp

vc100/boost_regex-vc100-mt-1_52/usinstances.obj: ../src/usinstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /EHsc /O2  /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /Zc:wchar_t /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/boost_regex-vc100-mt-1_52/ -Fdvc100/boost_regex-vc100-mt-1_52.pdb ../src/usinstances.cpp

vc100/boost_regex-vc100-mt-1_52/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /EHsc /O2  /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /Zc:wchar_t /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/boost_regex-vc100-mt-1_52/ -Fdvc100/boost_regex-vc100-mt-1_52.pdb ../src/w32_regex_traits.cpp

vc100/boost_regex-vc100-mt-1_52/wc_regex_traits.obj: ../src/wc_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /EHsc /O2  /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /Zc:wchar_t /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/boost_regex-vc100-mt-1_52/ -Fdvc100/boost_regex-vc100-mt-1_52.pdb ../src/wc_regex_traits.cpp

vc100/boost_regex-vc100-mt-1_52/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /EHsc /O2  /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /Zc:wchar_t /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/boost_regex-vc100-mt-1_52/ -Fdvc100/boost_regex-vc100-mt-1_52.pdb ../src/wide_posix_api.cpp

vc100/boost_regex-vc100-mt-1_52/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /EHsc /O2  /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /Zc:wchar_t /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/boost_regex-vc100-mt-1_52/ -Fdvc100/boost_regex-vc100-mt-1_52.pdb ../src/winstances.cpp

boost_regex-vc100-mt-1_52_dir :
	@if not exist "vc100\boost_regex-vc100-mt-1_52\$(NULL)" mkdir vc100\boost_regex-vc100-mt-1_52

boost_regex-vc100-mt-1_52_clean :
	del vc100\boost_regex-vc100-mt-1_52\*.obj
	del vc100\boost_regex-vc100-mt-1_52\*.idb
	del vc100\boost_regex-vc100-mt-1_52\*.exp
	del vc100\boost_regex-vc100-mt-1_52\*.pch

./vc100/boost_regex-vc100-mt-1_52.lib : vc100/boost_regex-vc100-mt-1_52/c_regex_traits.obj vc100/boost_regex-vc100-mt-1_52/cpp_regex_traits.obj vc100/boost_regex-vc100-mt-1_52/cregex.obj vc100/boost_regex-vc100-mt-1_52/fileiter.obj vc100/boost_regex-vc100-mt-1_52/icu.obj vc100/boost_regex-vc100-mt-1_52/instances.obj vc100/boost_regex-vc100-mt-1_52/posix_api.obj vc100/boost_regex-vc100-mt-1_52/regex.obj vc100/boost_regex-vc100-mt-1_52/regex_debug.obj vc100/boost_regex-vc100-mt-1_52/regex_raw_buffer.obj vc100/boost_regex-vc100-mt-1_52/regex_traits_defaults.obj vc100/boost_regex-vc100-mt-1_52/static_mutex.obj vc100/boost_regex-vc100-mt-1_52/usinstances.obj vc100/boost_regex-vc100-mt-1_52/w32_regex_traits.obj vc100/boost_regex-vc100-mt-1_52/wc_regex_traits.obj vc100/boost_regex-vc100-mt-1_52/wide_posix_api.obj vc100/boost_regex-vc100-mt-1_52/winstances.obj
	link kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /dll /incremental:yes /pdb:"vc100/boost_regex-vc100-mt-1_52.pdb" /debug /machine:I386 /out:"vc100/boost_regex-vc100-mt-1_52.dll" /implib:"vc100/boost_regex-vc100-mt-1_52.lib" /LIBPATH:"$(STLPORT_PATH)\lib" $(XLFLAGS) $(ICU_LINK_OPTS)  vc100/boost_regex-vc100-mt-1_52/c_regex_traits.obj vc100/boost_regex-vc100-mt-1_52/cpp_regex_traits.obj vc100/boost_regex-vc100-mt-1_52/cregex.obj vc100/boost_regex-vc100-mt-1_52/fileiter.obj vc100/boost_regex-vc100-mt-1_52/icu.obj vc100/boost_regex-vc100-mt-1_52/instances.obj vc100/boost_regex-vc100-mt-1_52/posix_api.obj vc100/boost_regex-vc100-mt-1_52/regex.obj vc100/boost_regex-vc100-mt-1_52/regex_debug.obj vc100/boost_regex-vc100-mt-1_52/regex_raw_buffer.obj vc100/boost_regex-vc100-mt-1_52/regex_traits_defaults.obj vc100/boost_regex-vc100-mt-1_52/static_mutex.obj vc100/boost_regex-vc100-mt-1_52/usinstances.obj vc100/boost_regex-vc100-mt-1_52/w32_regex_traits.obj vc100/boost_regex-vc100-mt-1_52/wc_regex_traits.obj vc100/boost_regex-vc100-mt-1_52/wide_posix_api.obj vc100/boost_regex-vc100-mt-1_52/winstances.obj

########################################################
#
# section for libboost_regex-vc100-mt-1_52.lib
#
########################################################
vc100/libboost_regex-vc100-mt-1_52/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /EHsc /O2  /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /Zc:wchar_t /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-1_52/ -Fdvc100/libboost_regex-vc100-mt-1_52.pdb ../src/c_regex_traits.cpp

vc100/libboost_regex-vc100-mt-1_52/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /EHsc /O2  /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /Zc:wchar_t /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-1_52/ -Fdvc100/libboost_regex-vc100-mt-1_52.pdb ../src/cpp_regex_traits.cpp

vc100/libboost_regex-vc100-mt-1_52/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /EHsc /O2  /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /Zc:wchar_t /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-1_52/ -Fdvc100/libboost_regex-vc100-mt-1_52.pdb ../src/cregex.cpp

vc100/libboost_regex-vc100-mt-1_52/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /EHsc /O2  /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /Zc:wchar_t /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-1_52/ -Fdvc100/libboost_regex-vc100-mt-1_52.pdb ../src/fileiter.cpp

vc100/libboost_regex-vc100-mt-1_52/icu.obj: ../src/icu.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /EHsc /O2  /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /Zc:wchar_t /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-1_52/ -Fdvc100/libboost_regex-vc100-mt-1_52.pdb ../src/icu.cpp

vc100/libboost_regex-vc100-mt-1_52/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /EHsc /O2  /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /Zc:wchar_t /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-1_52/ -Fdvc100/libboost_regex-vc100-mt-1_52.pdb ../src/instances.cpp

vc100/libboost_regex-vc100-mt-1_52/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /EHsc /O2  /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /Zc:wchar_t /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-1_52/ -Fdvc100/libboost_regex-vc100-mt-1_52.pdb ../src/posix_api.cpp

vc100/libboost_regex-vc100-mt-1_52/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /EHsc /O2  /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /Zc:wchar_t /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-1_52/ -Fdvc100/libboost_regex-vc100-mt-1_52.pdb ../src/regex.cpp

vc100/libboost_regex-vc100-mt-1_52/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /EHsc /O2  /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /Zc:wchar_t /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-1_52/ -Fdvc100/libboost_regex-vc100-mt-1_52.pdb ../src/regex_debug.cpp

vc100/libboost_regex-vc100-mt-1_52/regex_raw_buffer.obj: ../src/regex_raw_buffer.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /EHsc /O2  /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /Zc:wchar_t /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-1_52/ -Fdvc100/libboost_regex-vc100-mt-1_52.pdb ../src/regex_raw_buffer.cpp

vc100/libboost_regex-vc100-mt-1_52/regex_traits_defaults.obj: ../src/regex_traits_defaults.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /EHsc /O2  /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /Zc:wchar_t /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-1_52/ -Fdvc100/libboost_regex-vc100-mt-1_52.pdb ../src/regex_traits_defaults.cpp

vc100/libboost_regex-vc100-mt-1_52/static_mutex.obj: ../src/static_mutex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /EHsc /O2  /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /Zc:wchar_t /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-1_52/ -Fdvc100/libboost_regex-vc100-mt-1_52.pdb ../src/static_mutex.cpp

vc100/libboost_regex-vc100-mt-1_52/usinstances.obj: ../src/usinstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /EHsc /O2  /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /Zc:wchar_t /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-1_52/ -Fdvc100/libboost_regex-vc100-mt-1_52.pdb ../src/usinstances.cpp

vc100/libboost_regex-vc100-mt-1_52/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /EHsc /O2  /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /Zc:wchar_t /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-1_52/ -Fdvc100/libboost_regex-vc100-mt-1_52.pdb ../src/w32_regex_traits.cpp

vc100/libboost_regex-vc100-mt-1_52/wc_regex_traits.obj: ../src/wc_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /EHsc /O2  /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /Zc:wchar_t /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-1_52/ -Fdvc100/libboost_regex-vc100-mt-1_52.pdb ../src/wc_regex_traits.cpp

vc100/libboost_regex-vc100-mt-1_52/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /EHsc /O2  /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /Zc:wchar_t /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-1_52/ -Fdvc100/libboost_regex-vc100-mt-1_52.pdb ../src/wide_posix_api.cpp

vc100/libboost_regex-vc100-mt-1_52/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /EHsc /O2  /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /Zc:wchar_t /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-1_52/ -Fdvc100/libboost_regex-vc100-mt-1_52.pdb ../src/winstances.cpp

libboost_regex-vc100-mt-1_52_dir :
	@if not exist "vc100\libboost_regex-vc100-mt-1_52\$(NULL)" mkdir vc100\libboost_regex-vc100-mt-1_52

libboost_regex-vc100-mt-1_52_clean :
	del vc100\libboost_regex-vc100-mt-1_52\*.obj
	del vc100\libboost_regex-vc100-mt-1_52\*.idb
	del vc100\libboost_regex-vc100-mt-1_52\*.exp
	del vc100\libboost_regex-vc100-mt-1_52\*.pch

./vc100/libboost_regex-vc100-mt-1_52.lib : vc100/libboost_regex-vc100-mt-1_52/c_regex_traits.obj vc100/libboost_regex-vc100-mt-1_52/cpp_regex_traits.obj vc100/libboost_regex-vc100-mt-1_52/cregex.obj vc100/libboost_regex-vc100-mt-1_52/fileiter.obj vc100/libboost_regex-vc100-mt-1_52/icu.obj vc100/libboost_regex-vc100-mt-1_52/instances.obj vc100/libboost_regex-vc100-mt-1_52/posix_api.obj vc100/libboost_regex-vc100-mt-1_52/regex.obj vc100/libboost_regex-vc100-mt-1_52/regex_debug.obj vc100/libboost_regex-vc100-mt-1_52/regex_raw_buffer.obj vc100/libboost_regex-vc100-mt-1_52/regex_traits_defaults.obj vc100/libboost_regex-vc100-mt-1_52/static_mutex.obj vc100/libboost_regex-vc100-mt-1_52/usinstances.obj vc100/libboost_regex-vc100-mt-1_52/w32_regex_traits.obj vc100/libboost_regex-vc100-mt-1_52/wc_regex_traits.obj vc100/libboost_regex-vc100-mt-1_52/wide_posix_api.obj vc100/libboost_regex-vc100-mt-1_52/winstances.obj
	link -lib /nologo /out:vc100/libboost_regex-vc100-mt-1_52.lib $(XSFLAGS)  vc100/libboost_regex-vc100-mt-1_52/c_regex_traits.obj vc100/libboost_regex-vc100-mt-1_52/cpp_regex_traits.obj vc100/libboost_regex-vc100-mt-1_52/cregex.obj vc100/libboost_regex-vc100-mt-1_52/fileiter.obj vc100/libboost_regex-vc100-mt-1_52/icu.obj vc100/libboost_regex-vc100-mt-1_52/instances.obj vc100/libboost_regex-vc100-mt-1_52/posix_api.obj vc100/libboost_regex-vc100-mt-1_52/regex.obj vc100/libboost_regex-vc100-mt-1_52/regex_debug.obj vc100/libboost_regex-vc100-mt-1_52/regex_raw_buffer.obj vc100/libboost_regex-vc100-mt-1_52/regex_traits_defaults.obj vc100/libboost_regex-vc100-mt-1_52/static_mutex.obj vc100/libboost_regex-vc100-mt-1_52/usinstances.obj vc100/libboost_regex-vc100-mt-1_52/w32_regex_traits.obj vc100/libboost_regex-vc100-mt-1_52/wc_regex_traits.obj vc100/libboost_regex-vc100-mt-1_52/wide_posix_api.obj vc100/libboost_regex-vc100-mt-1_52/winstances.obj

########################################################
#
# section for libboost_regex-vc100-mt-gd-1_52.lib
#
########################################################
vc100/libboost_regex-vc100-mt-gd-1_52/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /EHsc /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /EHsc /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-gd-1_52/ -Fdvc100/libboost_regex-vc100-mt-gd-1_52.pdb ../src/c_regex_traits.cpp

vc100/libboost_regex-vc100-mt-gd-1_52/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /EHsc /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /EHsc /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-gd-1_52/ -Fdvc100/libboost_regex-vc100-mt-gd-1_52.pdb ../src/cpp_regex_traits.cpp

vc100/libboost_regex-vc100-mt-gd-1_52/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /EHsc /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /EHsc /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-gd-1_52/ -Fdvc100/libboost_regex-vc100-mt-gd-1_52.pdb ../src/cregex.cpp

vc100/libboost_regex-vc100-mt-gd-1_52/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /EHsc /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /EHsc /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-gd-1_52/ -Fdvc100/libboost_regex-vc100-mt-gd-1_52.pdb ../src/fileiter.cpp

vc100/libboost_regex-vc100-mt-gd-1_52/icu.obj: ../src/icu.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /EHsc /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /EHsc /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-gd-1_52/ -Fdvc100/libboost_regex-vc100-mt-gd-1_52.pdb ../src/icu.cpp

vc100/libboost_regex-vc100-mt-gd-1_52/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /EHsc /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /EHsc /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-gd-1_52/ -Fdvc100/libboost_regex-vc100-mt-gd-1_52.pdb ../src/instances.cpp

vc100/libboost_regex-vc100-mt-gd-1_52/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /EHsc /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /EHsc /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-gd-1_52/ -Fdvc100/libboost_regex-vc100-mt-gd-1_52.pdb ../src/posix_api.cpp

vc100/libboost_regex-vc100-mt-gd-1_52/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /EHsc /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /EHsc /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-gd-1_52/ -Fdvc100/libboost_regex-vc100-mt-gd-1_52.pdb ../src/regex.cpp

vc100/libboost_regex-vc100-mt-gd-1_52/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /EHsc /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /EHsc /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-gd-1_52/ -Fdvc100/libboost_regex-vc100-mt-gd-1_52.pdb ../src/regex_debug.cpp

vc100/libboost_regex-vc100-mt-gd-1_52/regex_raw_buffer.obj: ../src/regex_raw_buffer.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /EHsc /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /EHsc /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-gd-1_52/ -Fdvc100/libboost_regex-vc100-mt-gd-1_52.pdb ../src/regex_raw_buffer.cpp

vc100/libboost_regex-vc100-mt-gd-1_52/regex_traits_defaults.obj: ../src/regex_traits_defaults.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /EHsc /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /EHsc /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-gd-1_52/ -Fdvc100/libboost_regex-vc100-mt-gd-1_52.pdb ../src/regex_traits_defaults.cpp

vc100/libboost_regex-vc100-mt-gd-1_52/static_mutex.obj: ../src/static_mutex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /EHsc /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /EHsc /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-gd-1_52/ -Fdvc100/libboost_regex-vc100-mt-gd-1_52.pdb ../src/static_mutex.cpp

vc100/libboost_regex-vc100-mt-gd-1_52/usinstances.obj: ../src/usinstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /EHsc /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /EHsc /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-gd-1_52/ -Fdvc100/libboost_regex-vc100-mt-gd-1_52.pdb ../src/usinstances.cpp

vc100/libboost_regex-vc100-mt-gd-1_52/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /EHsc /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /EHsc /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-gd-1_52/ -Fdvc100/libboost_regex-vc100-mt-gd-1_52.pdb ../src/w32_regex_traits.cpp

vc100/libboost_regex-vc100-mt-gd-1_52/wc_regex_traits.obj: ../src/wc_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /EHsc /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /EHsc /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-gd-1_52/ -Fdvc100/libboost_regex-vc100-mt-gd-1_52.pdb ../src/wc_regex_traits.cpp

vc100/libboost_regex-vc100-mt-gd-1_52/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /EHsc /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /EHsc /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-gd-1_52/ -Fdvc100/libboost_regex-vc100-mt-gd-1_52.pdb ../src/wide_posix_api.cpp

vc100/libboost_regex-vc100-mt-gd-1_52/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /EHsc /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /EHsc /c $(CXXFLAGS) $(ICU_COMPILE_OPTS) -Y- -Fo./vc100/libboost_regex-vc100-mt-gd-1_52/ -Fdvc100/libboost_regex-vc100-mt-gd-1_52.pdb ../src/winstances.cpp

libboost_regex-vc100-mt-gd-1_52_dir :
	@if not exist "vc100\libboost_regex-vc100-mt-gd-1_52\$(NULL)" mkdir vc100\libboost_regex-vc100-mt-gd-1_52

libboost_regex-vc100-mt-gd-1_52_clean :
	del vc100\libboost_regex-vc100-mt-gd-1_52\*.obj
	del vc100\libboost_regex-vc100-mt-gd-1_52\*.idb
	del vc100\libboost_regex-vc100-mt-gd-1_52\*.exp
	del vc100\libboost_regex-vc100-mt-gd-1_52\*.pch

./vc100/libboost_regex-vc100-mt-gd-1_52.lib : vc100/libboost_regex-vc100-mt-gd-1_52/c_regex_traits.obj vc100/libboost_regex-vc100-mt-gd-1_52/cpp_regex_traits.obj vc100/libboost_regex-vc100-mt-gd-1_52/cregex.obj vc100/libboost_regex-vc100-mt-gd-1_52/fileiter.obj vc100/libboost_regex-vc100-mt-gd-1_52/icu.obj vc100/libboost_regex-vc100-mt-gd-1_52/instances.obj vc100/libboost_regex-vc100-mt-gd-1_52/posix_api.obj vc100/libboost_regex-vc100-mt-gd-1_52/regex.obj vc100/libboost_regex-vc100-mt-gd-1_52/regex_debug.obj vc100/libboost_regex-vc100-mt-gd-1_52/regex_raw_buffer.obj vc100/libboost_regex-vc100-mt-gd-1_52/regex_traits_defaults.obj vc100/libboost_regex-vc100-mt-gd-1_52/static_mutex.obj vc100/libboost_regex-vc100-mt-gd-1_52/usinstances.obj vc100/libboost_regex-vc100-mt-gd-1_52/w32_regex_traits.obj vc100/libboost_regex-vc100-mt-gd-1_52/wc_regex_traits.obj vc100/libboost_regex-vc100-mt-gd-1_52/wide_posix_api.obj vc100/libboost_regex-vc100-mt-gd-1_52/winstances.obj
	link -lib /nologo /out:vc100/libboost_regex-vc100-mt-gd-1_52.lib $(XSFLAGS)  vc100/libboost_regex-vc100-mt-gd-1_52/c_regex_traits.obj vc100/libboost_regex-vc100-mt-gd-1_52/cpp_regex_traits.obj vc100/libboost_regex-vc100-mt-gd-1_52/cregex.obj vc100/libboost_regex-vc100-mt-gd-1_52/fileiter.obj vc100/libboost_regex-vc100-mt-gd-1_52/icu.obj vc100/libboost_regex-vc100-mt-gd-1_52/instances.obj vc100/libboost_regex-vc100-mt-gd-1_52/posix_api.obj vc100/libboost_regex-vc100-mt-gd-1_52/regex.obj vc100/libboost_regex-vc100-mt-gd-1_52/regex_debug.obj vc100/libboost_regex-vc100-mt-gd-1_52/regex_raw_buffer.obj vc100/libboost_regex-vc100-mt-gd-1_52/regex_traits_defaults.obj vc100/libboost_regex-vc100-mt-gd-1_52/static_mutex.obj vc100/libboost_regex-vc100-mt-gd-1_52/usinstances.obj vc100/libboost_regex-vc100-mt-gd-1_52/w32_regex_traits.obj vc100/libboost_regex-vc100-mt-gd-1_52/wc_regex_traits.obj vc100/libboost_regex-vc100-mt-gd-1_52/wide_posix_api.obj vc100/libboost_regex-vc100-mt-gd-1_52/winstances.obj

