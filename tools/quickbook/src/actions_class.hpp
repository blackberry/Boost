/*=============================================================================
    Copyright (c) 2002 2004 2006 Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_ACTIONS_CLASS_HPP)
#define BOOST_SPIRIT_ACTIONS_CLASS_HPP

#include <boost/tuple/tuple.hpp>
#include <boost/scoped_ptr.hpp>
#include "actions.hpp"
#include "parsers.hpp"
#include "values_parse.hpp"
#include "collector.hpp"

namespace quickbook
{
    namespace cl = boost::spirit::classic;
    namespace fs = boost::filesystem;

    struct actions
    {
        actions(fs::path const& filein_, fs::path const& xinclude_base, string_stream& out_,
                id_generator&);

    private:
        boost::scoped_ptr<quickbook_grammar> grammar_;

    public:
    ///////////////////////////////////////////////////////////////////////////
    // State
    ///////////////////////////////////////////////////////////////////////////

        typedef std::vector<std::string> string_list;

        static int const max_template_depth = 100;

    // header info
        std::string             doc_type;
        std::string             doc_title_qbk;
        std::string             doc_id;

    // main output stream
        collector               out;

    // auxilliary streams
        collector               phrase;

    // value actions
        value_parser            values;
        to_value_action         to_value;
        phrase_to_docinfo_action docinfo_value;
        
        scoped_parser<cond_phrase_push>
                                scoped_cond_phrase;
        scoped_parser<scoped_output_push>
                                scoped_output;
        scoped_parser<set_no_eols_scoped>
                                scoped_no_eols;
        scoped_parser<scoped_context_impl>
                                scoped_context;

    // state
        fs::path                filename;
        fs::path                filename_relative;  // for the __FILENAME__ macro.
                                                    // (relative to the original file
                                                    //  or include path).
        fs::path                xinclude_base;
        std::size_t             macro_change_depth;
        string_symbols          macro;
        int                     section_level;
        int                     min_section_level;
        std::string             section_id;
        std::string             qualified_section_id;
        std::string             source_mode;

        typedef boost::tuple<
            fs::path
          , fs::path
          , std::size_t
          , int
          , int
          , std::string
          , std::string
          , std::string>
        state_tuple;

        std::stack<state_tuple> state_stack;
        // Stack macros separately as copying macros is expensive.
        std::stack<string_symbols> macro_stack;

    // temporary or global state
        int                     template_depth;
        template_stack          templates;
        int                     error_count;
        string_list             anchors;
        bool                    no_eols;
        bool                    suppress;
        bool                    warned_about_breaks;
        int                     context;
        id_generator&           ids;

    // push/pop the states and the streams
        void copy_macros_for_write();
        void push();
        void pop();
        quickbook_grammar& grammar() const;

    ///////////////////////////////////////////////////////////////////////////
    // actions
    ///////////////////////////////////////////////////////////////////////////

        element_action          element;
        error_action            error;

        code_action             code;
        code_action             code_block;
        inline_code_action      inline_code;
        paragraph_action        paragraph;
        space                   space_char;
        plain_char_action       plain_char;
        escape_unicode_action   escape_unicode;

        simple_phrase_action    simple_markup;

        break_action            break_;
        do_macro_action         do_macro;

        element_id_warning_action element_id_warning;
    };
}

#endif // BOOST_SPIRIT_ACTIONS_CLASS_HPP

