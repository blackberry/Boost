/*=============================================================================
    Copyright (c) 2010-2011 Daniel James

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#if !defined(BOOST_SPIRIT_QUICKBOOK_VALUES_PARSE_HPP)
#define BOOST_SPIRIT_QUICKBOOK_VALUES_PARSE_HPP

#include "values.hpp"
#include "parsers.hpp"
#include "scoped.hpp"
#include <boost/spirit/include/phoenix1_functions.hpp>

#include <iostream>

namespace quickbook {
    namespace ph = phoenix;

    struct value_builder_save : scoped_action_base
    {
        value_builder_save(value_builder& builder) : builder(builder) {}

        bool start()
        {
            builder.save();
            return true;
        }

        void cleanup() { builder.restore(); }

        value_builder& builder;
    };

    struct value_builder_list : scoped_action_base
    {
        value_builder_list(value_builder& builder) : builder(builder) {}

        bool start(value::tag_type tag = value::default_tag)
        {
            builder.start_list(tag);
            return true;
        }

        void success() { builder.finish_list(); }
        void failure() { builder.clear_list(); }

        value_builder& builder;
    };

    struct value_entry
    {
        template <typename Arg1, typename Arg2 = void, typename Arg3 = void, typename Arg4 = void>
        struct result {
            typedef void type;
        };

        value_entry(value_builder& b)
            : b(b) {}

        template <typename Iterator>
        void operator()(Iterator begin, Iterator end,
                value::tag_type tag = value::default_tag) const
        {
            b.insert(qbk_value(begin, end, tag));
        }

        template <typename Iterator>
        void operator()(Iterator begin, Iterator,
                std::string const& v,
                value::tag_type tag = value::default_tag) const
        {
            b.insert(qbk_value(v, begin.get_position(), tag));
        }
        
        void operator()(int v,
            value::tag_type tag = value::default_tag) const
        {
            b.insert(int_value(v, tag));
        }

        value_builder& b;
    };

    struct value_reset
    {
        typedef void result_type;
    
        value_reset(value_builder& b)
            : b(b) {}

        void operator()() const {
            b.reset();
        }

        value_builder& b;
    };
    
    struct value_sort
    {
        typedef void result_type;
    
        value_sort(value_builder& b)
            : b(b) {}

        void operator()() const {
            b.sort_list();
        }

        value_builder& b;
    };

    struct value_parser
    {
        value_parser()
            : builder()
            , save(builder)
            , list(builder)
            , entry(builder)
            , reset(builder)
            , sort(builder)
            {}
    
        value release() { return builder.release(); }

        value_builder builder;
        scoped_parser<value_builder_save> save;
        scoped_parser<value_builder_list> list;
        ph::function<value_entry> entry;
        ph::function<value_reset> reset;
        ph::function<value_sort> sort;
    };
}

#endif
