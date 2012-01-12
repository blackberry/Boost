/*=============================================================================
    Copyright (c) 2002 2004 2006 Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    Copyright (c) 2010 Daniel James
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_FWD_HPP)
#define BOOST_SPIRIT_FWD_HPP

#include "iterator.hpp"

namespace quickbook
{
    struct actions;
    struct quickbook_grammar;
    struct collector;
    struct id_generator;

    typedef position_iterator<std::string::const_iterator> iterator;

    inline void ignore_variable(void const*) {} 
}

#endif
