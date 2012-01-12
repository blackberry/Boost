/*=============================================================================
    Copyright (c) 2006 Joel de Guzman
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#include <boost/spirit/include/classic_core.hpp>
#include <boost/spirit/include/classic_actor.hpp>
#include <boost/spirit/include/classic_confix.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include "template_stack.hpp"
#include "actions.hpp"
#include "values.hpp"

namespace quickbook
{
    namespace cl = boost::spirit::classic;

    struct code_snippet_actions
    {
        code_snippet_actions(std::vector<template_symbol>& storage,
                                 fs::path const& filename,
                                 std::string const& doc_id,
                                 char const* source_type)
            : callout_id(0)
            , storage(storage)
            , filename(filename)
            , doc_id(doc_id)
            , source_type(source_type)
        {}

        void pass_thru_char(char);
        void pass_thru(iterator first, iterator last);
        void escaped_comment(iterator first, iterator last);
        void start_snippet(iterator first, iterator last);
        void end_snippet(iterator first, iterator last);
        void callout(iterator first, iterator last);
        
        void append_code();
        void close_code();

        struct snippet_data
        {
            snippet_data(std::string const& id, int callout_base_id)
                : id(id)
                , callout_base_id(callout_base_id)
                , content()
                , start_code(false)
                , end_code(false)
            {}
            
            std::string id;
            int callout_base_id;
            std::string content;
            bool start_code;
            bool end_code;
            value_builder callouts;
            boost::shared_ptr<snippet_data> next;
        };
        
        void push_snippet_data(std::string const& id, int callout_base_id)
        {
            boost::shared_ptr<snippet_data> new_snippet(
                new snippet_data(id, callout_base_id));
            new_snippet->next = snippet_stack;
            snippet_stack = new_snippet;
        }

        boost::shared_ptr<snippet_data> pop_snippet_data()
        {
            boost::shared_ptr<snippet_data> snippet(snippet_stack);
            snippet_stack = snippet->next;
            snippet->next.reset();
            return snippet;
        }
        
        int callout_id;
        boost::shared_ptr<snippet_data> snippet_stack;
        std::string code;
        std::string id;
        std::vector<template_symbol>& storage;
        fs::path filename;
        std::string const doc_id;
        char const* const source_type;
    };

    struct python_code_snippet_grammar
        : cl::grammar<python_code_snippet_grammar>
    {
        typedef code_snippet_actions actions_type;
  
        python_code_snippet_grammar(actions_type & actions)
            : actions(actions)
        {}

        template <typename Scanner>
        struct definition
        {
            typedef code_snippet_actions actions_type;
            
            definition(python_code_snippet_grammar const& self)
            {

                actions_type& actions = self.actions;
            
                start_ = *code_elements;

                identifier =
                    (cl::alpha_p | '_') >> *(cl::alnum_p | '_')
                    ;

                code_elements =
                        start_snippet               [boost::bind(&actions_type::start_snippet, &actions, _1, _2)]
                    |   end_snippet                 [boost::bind(&actions_type::end_snippet, &actions, _1, _2)]
                    |   escaped_comment
                    |   pass_thru_comment
                    |   ignore
                    |   cl::anychar_p               [boost::bind(&actions_type::pass_thru_char, &actions, _1)]
                    ;

                start_snippet =
                    "#[" >> *cl::space_p
                    >> identifier                   [cl::assign_a(actions.id)]
                    ;

                end_snippet =
                    cl::str_p("#]")
                    ;

                ignore
                    =   cl::confix_p(
                            *cl::blank_p >> "#<-",
                            *cl::anychar_p,
                            "#->" >> *cl::blank_p >> cl::eol_p
                        )
                    |   cl::confix_p(
                            "\"\"\"<-\"\"\"",
                            *cl::anychar_p,
                            "\"\"\"->\"\"\""
                        )
                    |   cl::confix_p(
                            "\"\"\"<-",
                            *cl::anychar_p,
                            "->\"\"\""
                        )
                    ;

                escaped_comment =
                        cl::confix_p(
                            *cl::space_p >> "#`",
                            (*cl::anychar_p)        [boost::bind(&actions_type::escaped_comment, &actions, _1, _2)],
                            cl::eol_p
                        )
                    |   cl::confix_p(
                            *cl::space_p >> "\"\"\"`",
                            (*cl::anychar_p)        [boost::bind(&actions_type::escaped_comment, &actions, _1, _2)],
                            "\"\"\""
                        )
                    ;

                // Note: Unlike escaped_comment and ignore, this doesn't
                // swallow preceeding whitespace.
                pass_thru_comment
                    =   "#=" >> (cl::eps_p - '=')
                    >>  (   *(cl::anychar_p - cl::eol_p)
                        >>  (cl::eol_p | cl::end_p)
                        )                           [boost::bind(&actions_type::pass_thru, &actions, _1, _2)]
                    |   cl::confix_p(
                            "\"\"\"=" >> (cl::eps_p - '='),
                            (*cl::anychar_p)        [boost::bind(&actions_type::pass_thru, &actions, _1, _2)],
                            "\"\"\""
                        )
                    ;
            }

            cl::rule<Scanner>
                start_, identifier, code_elements, start_snippet, end_snippet,
                escaped_comment, pass_thru_comment, ignore;

            cl::rule<Scanner> const&
            start() const { return start_; }
        };

        actions_type& actions;
    };  

    struct cpp_code_snippet_grammar
        : cl::grammar<cpp_code_snippet_grammar>
    {
        typedef code_snippet_actions actions_type;
  
        cpp_code_snippet_grammar(actions_type & actions)
            : actions(actions)
        {}

        template <typename Scanner>
        struct definition
        {
            definition(cpp_code_snippet_grammar const& self)
            {
                actions_type& actions = self.actions;
            
                start_ = *code_elements;

                identifier =
                    (cl::alpha_p | '_') >> *(cl::alnum_p | '_')
                    ;

                code_elements =
                        start_snippet               [boost::bind(&actions_type::start_snippet, &actions, _1, _2)]
                    |   end_snippet                 [boost::bind(&actions_type::end_snippet, &actions, _1, _2)]
                    |   escaped_comment
                    |   ignore
                    |   pass_thru_comment
                    |   line_callout
                    |   inline_callout
                    |   cl::anychar_p               [boost::bind(&actions_type::pass_thru_char, &actions, _1)]
                    ;

                start_snippet =
                        "//[" >> *cl::space_p
                        >> identifier               [cl::assign_a(actions.id)]
                    |
                        "/*[" >> *cl::space_p
                        >> identifier               [cl::assign_a(actions.id)]
                        >> *cl::space_p >> "*/"
                    ;

                end_snippet =
                    cl::str_p("//]") | "/*]*/"
                    ;

                inline_callout
                    =   cl::confix_p(
                            "/*<" >> *cl::space_p,
                            (*cl::anychar_p)        [boost::bind(&actions_type::callout, &actions, _1, _2)],
                            ">*/"
                        )
                        ;

                line_callout
                    =   cl::confix_p(
                            "/*<<" >> *cl::space_p,
                            (*cl::anychar_p)        [boost::bind(&actions_type::callout, &actions, _1, _2)],
                            ">>*/"
                        )
                    >>  *cl::space_p
                    ;

                ignore
                    =   cl::confix_p(
                            *cl::blank_p >> "//<-",
                            *cl::anychar_p,
                            "//->"
                        )
                    >>  *cl::blank_p
                    >>  cl::eol_p
                    |   cl::confix_p(
                            "/*<-*/",
                            *cl::anychar_p,
                            "/*->*/"
                        )
                    |   cl::confix_p(
                            "/*<-",
                            *cl::anychar_p,
                            "->*/"
                        )
                    ;

                escaped_comment
                    =   cl::confix_p(
                            *cl::space_p >> "//`",
                            (*cl::anychar_p)        [boost::bind(&actions_type::escaped_comment, &actions, _1, _2)],
                            cl::eol_p
                        )
                    |   cl::confix_p(
                            *cl::space_p >> "/*`",
                            (*cl::anychar_p)        [boost::bind(&actions_type::escaped_comment, &actions, _1, _2)],
                            "*/"
                        )
                    ;

                // Note: Unlike escaped_comment and ignore, this doesn't
                // swallow preceeding whitespace.
                pass_thru_comment
                    =   "//=" >> (cl::eps_p - '=')
                    >>  (   *(cl::anychar_p - cl::eol_p)
                        >>  (cl::eol_p | cl::end_p)
                        )                           [boost::bind(&actions_type::pass_thru, &actions, _1, _2)]
                    |   cl::confix_p(
                            "/*=" >> (cl::eps_p - '='),
                            (*cl::anychar_p)        [boost::bind(&actions_type::pass_thru, &actions, _1, _2)],
                            "*/"
                        )
                    ;
            }

            cl::rule<Scanner>
            start_, identifier, code_elements, start_snippet, end_snippet,
                escaped_comment, pass_thru_comment, inline_callout, line_callout, ignore;

            cl::rule<Scanner> const&
            start() const { return start_; }
        };

        actions_type& actions;
    };

    int load_snippets(
        fs::path const& file
      , std::vector<template_symbol>& storage   // snippets are stored in a
                                                // vector of template_symbols
      , std::string const& extension
      , std::string const& doc_id)
    {
        std::string code;
        int err = detail::load(file, code);
        if (err != 0)
            return err; // return early on error

        iterator first(code.begin());
        iterator last(code.end());

        bool is_python = extension == ".py";
        code_snippet_actions a(storage, file, doc_id, is_python ? "[python]" : "[c++]");
        // TODO: Should I check that parse succeeded?
        if(is_python) {
            boost::spirit::classic::parse(first, last, python_code_snippet_grammar(a));
        }
        else {
            boost::spirit::classic::parse(first, last, cpp_code_snippet_grammar(a));
        }

        return 0;
    }

    void code_snippet_actions::append_code()
    {
        if(!snippet_stack) return;
        snippet_data& snippet = *snippet_stack;
    
        if (!code.empty())
        {
            detail::unindent(code); // remove all indents

            if(snippet.content.empty())
            {
                snippet.start_code = true;
            }
            else if(!snippet.end_code)
            {
                snippet.content += "\n\n";
                snippet.content += source_type;
                snippet.content += "```\n";
            }
            
            snippet.content += code;
            snippet.end_code = true;

            code.clear();
        }
    }

    void code_snippet_actions::close_code()
    {
        if(!snippet_stack) return;
        snippet_data& snippet = *snippet_stack;
    
        if(snippet.end_code)
        {
            snippet.content += "```\n\n";
            snippet.end_code = false;
        }
    }

    void code_snippet_actions::pass_thru(iterator first, iterator last)
    {
        if(!snippet_stack) return;
        code.append(first, last);
    }

    void code_snippet_actions::pass_thru_char(char c)
    {
        if(!snippet_stack) return;
        code += c;
    }

    void code_snippet_actions::callout(iterator first, iterator last)
    {
        if(!snippet_stack) return;
        code += "``[[callout" + boost::lexical_cast<std::string>(callout_id) + "]]``";
    
        snippet_stack->callouts.insert(qbk_value(first, last, template_tags::block));
        ++callout_id;
    }

    void code_snippet_actions::escaped_comment(iterator first, iterator last)
    {
        if(!snippet_stack) return;
        snippet_data& snippet = *snippet_stack;
        append_code();
        close_code();

        std::string temp(first, last);
        detail::unindent(temp); // remove all indents
        if (temp.size() != 0)
        {
            snippet.content += "\n" + temp; // add a linebreak to allow block markups
        }
    }

    void code_snippet_actions::start_snippet(iterator, iterator)
    {
        append_code();
        push_snippet_data(id, callout_id);
        id.clear();
    }

    void code_snippet_actions::end_snippet(iterator first, iterator)
    {
        // TODO: Error?
        if(!snippet_stack) return;

        append_code();

        boost::shared_ptr<snippet_data> snippet = pop_snippet_data();
        value callouts = snippet->callouts.release();

        std::string body;
        if(snippet->start_code) {
            body += "\n\n";
            body += source_type;
            body += "```\n";
        }
        body += snippet->content;
        if(snippet->end_code) {
            body += "```\n\n";
        }

        std::vector<std::string> params;
        int i = 0;
        for(value::iterator it = callouts.begin(); it != callouts.end(); ++it)
        {
            params.push_back("[callout" + boost::lexical_cast<std::string>(snippet->callout_base_id + i) + "]");
            ++i;
        }
        
        // TODO: Save position in start_snippet
        template_symbol symbol(snippet->id, params,
            qbk_value(body, first.get_position(), template_tags::block),
            filename);
        symbol.callouts = callouts;
        storage.push_back(symbol);

        // Merge the snippet into its parent

        if(snippet_stack)
        {
            snippet_data& next = *snippet_stack;
            if(!snippet->content.empty()) {
                if(!snippet->start_code) {
                    close_code();
                }
                else if(!next.end_code) {
                    next.content += "\n\n";
                    next.content += source_type;
                    next.content += "```\n";
                }
                
                next.content += snippet->content;
                next.end_code = snippet->end_code;
            }

            next.callouts.extend(callouts);
        }
    }
}
