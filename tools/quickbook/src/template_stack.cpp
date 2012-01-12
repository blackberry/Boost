/*=============================================================================
    Copyright (c) 2002 2004 2006 Joel de Guzman
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#include <cassert>
#include "template_stack.hpp"

#ifdef BOOST_MSVC
#pragma warning(disable : 4355)
#endif

namespace quickbook
{
    template_body::template_body(
            value const& content,
            fs::path const& filename,
            content_type type
        )
        : content(content)
        , filename(filename)
        , type(type)
    {
        assert(content.get_tag() == template_tags::block ||
            content.get_tag() == template_tags::phrase);
    }

    bool template_body::is_block() const
    {
        return content.get_tag() == template_tags::block;
    }

    template_stack::template_stack()
        : scope(template_stack::parser(*this))
        , scopes()
    {
        scopes.push_front(template_scope());
    }
    
    template_symbol* template_stack::find(std::string const& symbol) const
    {
        for (template_scope const* i = &*scopes.begin(); i; i = i->parent_scope)
        {
            if (template_symbol* ts = boost::spirit::classic::find(i->symbols, symbol.c_str()))
                return ts;
        }
        return 0;
    }

    template_symbol* template_stack::find_top_scope(std::string const& symbol) const
    {
        return boost::spirit::classic::find(scopes.front().symbols, symbol.c_str());
    }

    template_symbols const& template_stack::top() const
    {
        BOOST_ASSERT(!scopes.empty());
        return scopes.front().symbols;
    }

    template_scope const& template_stack::top_scope() const
    {
        BOOST_ASSERT(!scopes.empty());
        return scopes.front();
    }
    
    // TODO: Should symbols defined by '[import]' use the current scope?
    bool template_stack::add(template_symbol const& ts)
    {
        BOOST_ASSERT(!scopes.empty());
        BOOST_ASSERT(ts.parent);
        
        if (this->find_top_scope(ts.identifier)) {
            return false;
        }
        
        boost::spirit::classic::add(scopes.front().symbols,
            ts.identifier.c_str(), ts);

        return true;
    }
    
    void template_stack::push()
    {
        template_scope const& old_front = scopes.front();
        scopes.push_front(template_scope());
        set_parent_scope(old_front);
    }

    void template_stack::pop()
    {
        scopes.pop_front();
    }

    void template_stack::set_parent_scope(template_scope const& parent)
    {
        scopes.front().parent_scope = &parent;
    }
}


