/*=============================================================================
    Copyright (c) 2002 2004 2006 Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_QUICKBOOK_ACTIONS_HPP)
#define BOOST_SPIRIT_QUICKBOOK_ACTIONS_HPP

#include <string>
#include <vector>
#include <boost/spirit/include/phoenix1_functions.hpp>
#include <boost/spirit/include/classic_symbols_fwd.hpp>
#include "fwd.hpp"
#include "template_stack.hpp"
#include "utils.hpp"
#include "values.hpp"
#include "scoped.hpp"

namespace quickbook
{
    namespace cl = boost::spirit::classic;

    extern unsigned qbk_version_n; // qbk_major_version * 100 + qbk_minor_version

    struct quickbook_range {
        template <typename Arg>
        struct result
        {
            typedef bool type;
        };
        
        quickbook_range(unsigned min_, unsigned max_)
            : min_(min_), max_(max_) {}
        
        bool operator()() const {
            return qbk_version_n >= min_ && qbk_version_n < max_;
        }

        unsigned min_, max_;
    };
    
    inline quickbook_range qbk_since(unsigned min_) {
        return quickbook_range(min_, 999);
    }
    
    inline quickbook_range qbk_before(unsigned max_) {
        return quickbook_range(0, max_);
    }

    typedef cl::symbols<std::string> string_symbols;

    int load_snippets(fs::path const& file, std::vector<template_symbol>& storage,
        std::string const& extension, std::string const& doc_id);

    std::string syntax_highlight(
        iterator first, iterator last,
        actions& escape_actions,
        std::string const& source_mode);        

    struct error_message_action
    {
        // Prints an error message to std::cerr

        error_message_action(quickbook::actions& actions, std::string const& m)
            : actions(actions)
            , message(m)
        {}

        void operator()(iterator, iterator) const;

        quickbook::actions& actions;
        std::string message;
    };

    struct error_action
    {
        // Prints an error message to std::cerr

        error_action(quickbook::actions& actions)
        : actions(actions) {}

        void operator()(iterator first, iterator /*last*/) const;

        error_message_action operator()(std::string const& message)
        {
            return error_message_action(actions, message);
        }

        quickbook::actions& actions;
    };

    struct element_action
    {
        element_action(quickbook::actions& actions)
            : actions(actions) {}

        void operator()(iterator, iterator) const;

        quickbook::actions& actions;
    };

    struct paragraph_action
    {
        //  implicit paragraphs
        //  doesn't output the paragraph if it's only whitespace.

        paragraph_action(
            quickbook::actions& actions)
        : actions(actions) {}

        void operator()() const;
        void operator()(iterator, iterator) const { (*this)(); }

        quickbook::actions& actions;
    };

    struct simple_phrase_action
    {
        //  Handles simple text formats

        simple_phrase_action(
            collector& out
          , quickbook::actions& actions)
        : out(out)
        , actions(actions) {}

        void operator()(char) const;

        collector& out;
        quickbook::actions& actions;
    };

    struct cond_phrase_push : scoped_action_base
    {
        cond_phrase_push(quickbook::actions& x)
            : actions(x) {}

        bool start();
        void cleanup();

        quickbook::actions& actions;
        bool saved_suppress;
    };

    struct span
    {
        // Decorates c++ code fragments

        span(char const* name, collector& out)
        : name(name), out(out) {}

        void operator()(iterator first, iterator last) const;

        char const* name;
        collector& out;
    };

    struct span_start
    {
        span_start(char const* name, collector& out)
        : name(name), out(out) {}

        void operator()(iterator first, iterator last) const;

        char const* name;
        collector& out;
    };

    struct span_end
    {
        span_end(collector& out)
        : out(out) {}

        void operator()(iterator first, iterator last) const;

        collector& out;
    };

    struct unexpected_char
    {
        // Handles unexpected chars in c++ syntax

        unexpected_char(
            collector& out
          , quickbook::actions& actions)
        : out(out)
        , actions(actions) {}

        void operator()(iterator first, iterator last) const;

        collector& out;
        quickbook::actions& actions;
    };

    extern char const* quickbook_get_date;
    extern char const* quickbook_get_time;

    struct do_macro_action
    {
        // Handles macro substitutions

        do_macro_action(collector& phrase, quickbook::actions& actions)
            : phrase(phrase)
            , actions(actions) {}

        void operator()(std::string const& str) const;
        collector& phrase;
        quickbook::actions& actions;
    };

    struct space
    {
        // Prints a space

        space(collector& out)
            : out(out) {}

        void operator()(iterator first, iterator last) const;
        void operator()(char ch) const;

        collector& out;
    };

    struct pre_escape_back
    {
        // Escapes back from code to quickbook (Pre)

        pre_escape_back(actions& escape_actions, std::string& save)
            : escape_actions(escape_actions), save(save) {}

        void operator()(iterator first, iterator last) const;

        actions& escape_actions;
        std::string& save;
    };

    struct post_escape_back
    {
        // Escapes back from code to quickbook (Post)

        post_escape_back(collector& out, actions& escape_actions, std::string& save)
            : out(out), escape_actions(escape_actions), save(save) {}

        void operator()(iterator first, iterator last) const;

        collector& out;
        actions& escape_actions;
        std::string& save;
    };

    struct plain_char_action
    {
        // Prints a single plain char.
        // Converts '<' to "&lt;"... etc See utils.hpp

        plain_char_action(collector& phrase, quickbook::actions& actions)
        : phrase(phrase)
        , actions(actions) {}

        void operator()(char ch) const;
        void operator()(iterator first, iterator /*last*/) const;

        collector& phrase;
        quickbook::actions& actions;
    };
    
    struct escape_unicode_action
    {
        escape_unicode_action(collector& phrase, quickbook::actions& actions)
        : phrase(phrase)
        , actions(actions) {}
        void operator()(iterator first, iterator last) const;

        collector& phrase;
        quickbook::actions& actions;
    };

    struct code_action
    {
        // Does the actual syntax highlighing of code

        code_action(
            collector& out
          , collector& phrase
          , quickbook::actions& actions)
        : out(out)
        , phrase(phrase)
        , actions(actions)
        {
        }

        void operator()(iterator first, iterator last) const;

        collector& out;
        collector& phrase;
        quickbook::actions& actions;
    };

    struct inline_code_action
    {
        // Does the actual syntax highlighing of code inlined in text

        inline_code_action(
            collector& out
          , quickbook::actions& actions)
        : out(out)
        , actions(actions)
        {}

        void operator()(iterator first, iterator last) const;

        collector& out;
        quickbook::actions& actions;
    };

    struct break_action
    {
        // Handles line-breaks (DEPRECATED!!!)

        break_action(collector& phrase, quickbook::actions& actions)
        : phrase(phrase), actions(actions) {}

        void operator()(iterator f, iterator) const;

        collector& phrase;
        quickbook::actions& actions;
    };

   struct element_id_warning_action
   {
        element_id_warning_action(quickbook::actions& actions_)
            : actions(actions_) {}

        void operator()(iterator first, iterator last) const;

        quickbook::actions& actions;
   };

    void pre(collector& out, quickbook::actions& actions, bool ignore_docinfo = false);
    void post(collector& out, quickbook::actions& actions, bool ignore_docinfo = false);

    struct phrase_to_docinfo_action_impl
    {
        template <typename Arg1, typename Arg2, typename Arg3 = void>
        struct result { typedef void type; };
    
        phrase_to_docinfo_action_impl(quickbook::actions& actions)
            : actions(actions) {}

        void operator()(iterator first, iterator last) const;
        void operator()(iterator first, iterator last, value::tag_type) const;

        quickbook::actions& actions;
    };
    
    typedef phoenix::function<phrase_to_docinfo_action_impl> phrase_to_docinfo_action;

    struct to_value_action
    {
        to_value_action(quickbook::actions& actions)
            : actions(actions) {}

        void operator()(iterator first, iterator last) const;

        quickbook::actions& actions;
    };

    struct scoped_output_push : scoped_action_base
    {
        scoped_output_push(quickbook::actions& actions)
            : actions(actions) {}

        bool start();
        void cleanup();

        quickbook::actions& actions;
        std::vector<std::string> saved_anchors;
    };

    struct set_no_eols_scoped : scoped_action_base
    {
        set_no_eols_scoped(quickbook::actions& actions)
            : actions(actions) {}

        bool start();
        void cleanup();

        quickbook::actions& actions;
        bool saved_no_eols;
    };
    
    struct scoped_context_impl : scoped_action_base
    {
        scoped_context_impl(quickbook::actions& actions)
            : actions_(actions) {}

        bool start(int);
        void cleanup();

    private:
        quickbook::actions& actions_;
        int saved_context_;
    };
}

#endif // BOOST_SPIRIT_QUICKBOOK_ACTIONS_HPP
