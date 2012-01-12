/*=============================================================================
    Copyright (c) 2002 2004 2006 Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    Copyright (c) 2005 Thomas Guest
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#include "actions_class.hpp"
#include "quickbook.hpp"
#include "grammar.hpp"
#include "input_path.hpp"

#if (defined(BOOST_MSVC) && (BOOST_MSVC <= 1310))
#pragma warning(disable:4355)
#endif

namespace quickbook
{
    actions::actions(fs::path const& filein_, fs::path const& xinclude_base_,
            string_stream& out_, id_generator& ids)
        : grammar_()

    // header info
        , doc_type()
        , doc_title_qbk()
        , doc_id()

    // main output stream
        , out(out_)

    // auxilliary streams
        , phrase()

    // value actions
        , values()
        , to_value(*this)
        , docinfo_value(*this)
        , scoped_cond_phrase(*this)
        , scoped_output(*this)
        , scoped_no_eols(*this)
        , scoped_context(*this)

    // state
        , filename(filein_)
        , filename_relative(filein_.filename())
        , xinclude_base(xinclude_base_)
        , macro_change_depth(0)
        , macro()
        , section_level(0)
        , min_section_level(0)
        , section_id()
        , qualified_section_id()
        , source_mode("c++")

    // temporary or global state
        , template_depth(0)
        , templates()
        , error_count(0)
        , anchors()
        , no_eols(true)
        , suppress(false)
        , warned_about_breaks(false)
        , context(0)
        , ids(ids)

    // actions
        , element(*this)
        , error(*this)
        , code(out, phrase, *this)
        , code_block(phrase, phrase, *this)
        , inline_code(phrase, *this)
        , paragraph(*this)
        , space_char(phrase)
        , plain_char(phrase, *this)
        , escape_unicode(phrase, *this)

        , simple_markup(phrase, *this)

        , break_(phrase, *this)
        , do_macro(phrase, *this)

        , element_id_warning(*this)
    {
        // add the predefined macros
        macro.add
            ("__DATE__", std::string(quickbook_get_date))
            ("__TIME__", std::string(quickbook_get_time))
            ("__FILENAME__", detail::path_to_generic(filename_relative))
        ;
        
        boost::scoped_ptr<quickbook_grammar> g(
            new quickbook_grammar(*this));
        grammar_.swap(g);
    }
    
    void actions::push()
    {
        state_stack.push(
            boost::make_tuple(
                filename
              , xinclude_base
              , macro_change_depth
              , section_level
              , min_section_level
              , section_id
              , qualified_section_id
              , source_mode
            )
        );

        out.push();
        phrase.push();
        templates.push();
        values.builder.save();
    }
    
    // Pushing and popping the macro symbol table is pretty expensive, so
    // instead implement a sort of 'stack on write'. Call this whenever a
    // change is made to the macro table, and it'll stack the current macros
    // if necessary. Would probably be better to implement macros in a less
    // expensive manner.
    void actions::copy_macros_for_write()
    {
        if(macro_change_depth != state_stack.size())
        {
            macro_stack.push(macro);
            macro_change_depth = state_stack.size();
        }
    }

    void actions::pop()
    {
        if(macro_change_depth == state_stack.size())
        {
            macro = macro_stack.top();
            macro_stack.pop();
        }
    
        boost::tie(
            filename
          , xinclude_base
          , macro_change_depth
          , section_level
          , min_section_level
          , section_id
          , qualified_section_id
          , source_mode
        ) = state_stack.top();
        state_stack.pop();

        out.pop();
        phrase.pop();
        templates.pop();
        values.builder.restore();
    }
    
    quickbook_grammar& actions::grammar() const {
        return *grammar_;
    }
}
