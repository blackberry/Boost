/*=============================================================================
    Copyright (c) 2002 2004 2006 Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#include "grammar_impl.hpp"
#include "actions_class.hpp"
#include "utils.hpp"
#include "template_tags.hpp"
#include "block_tags.hpp"
#include "phrase_tags.hpp"
#include "parsers.hpp"
#include "scoped.hpp"
#include <boost/spirit/include/classic_core.hpp>
#include <boost/spirit/include/classic_chset.hpp>
#include <boost/spirit/include/classic_if.hpp>
#include <boost/spirit/include/classic_loops.hpp>
#include <boost/spirit/include/classic_attribute.hpp>
#include <boost/spirit/include/classic_lazy.hpp>
#include <boost/spirit/include/phoenix1_primitives.hpp>

namespace quickbook
{
    namespace cl = boost::spirit::classic;

    struct main_grammar_local
    {
        struct process_element_impl : scoped_action_base {
            process_element_impl(main_grammar_local& l)
                : l(l) {}

            bool start()
            {
                if (!(l.info.type & l.actions_.context) ||
                        qbk_version_n < l.info.qbk_version)
                    return false;

                info_ = l.info;

                if (!(info_.type & element_info::in_phrase))
                    l.actions_.paragraph();

                l.actions_.values.builder.reset();
                
                return true;
            }
            
            template <typename ResultT, typename ScannerT>
            bool result(ResultT result, ScannerT const& scan)
            {
                if (result || info_.type & element_info::in_phrase)
                    return result;

                l.actions_.error(scan.first, scan.first);
                return true;
            }

            void success() { l.element_type = info_.type; }
            void failure() { l.element_type = element_info::nothing; }

            main_grammar_local& l;
            element_info info_;
        };
        
        struct is_block_type
        {
            typedef bool result_type;
            template <typename Arg1 = void>
            struct result { typedef bool type; };
        
            is_block_type(main_grammar_local& l)
                : l_(l)
            {}

            bool operator()() const
            {
                return l_.element_type && !(l_.element_type & element_info::in_phrase);
            }
            
            main_grammar_local& l_;
        };

        cl::rule<scanner>
                        top_level, blocks, paragraph_separator,
                        code, code_line, blank_line, hr,
                        list, list_item,
                        escape,
                        inline_code,
                        template_,
                        code_block, macro,
                        template_args,
                        template_args_1_4, template_arg_1_4,
                        template_inner_arg_1_4, brackets_1_4,
                        template_args_1_5, template_arg_1_5, template_arg_1_5_content,
                        template_inner_arg_1_5, brackets_1_5,
                        break_,
                        command_line_macro_identifier, command_line_phrase,
                        dummy_block
                        ;

        cl::rule<scanner> element;

        struct simple_markup_closure
            : cl::closure<simple_markup_closure, char>
        {
            member1 mark;
        };

        cl::rule<scanner, simple_markup_closure::context_t> simple_markup;
        cl::rule<scanner> simple_markup_end;

        element_info info;
        element_info::type_enum element_type;

        quickbook::actions& actions_;
        scoped_parser<process_element_impl> process_element;
        is_block_type is_block;

        main_grammar_local(quickbook::actions& actions)
            : actions_(actions)
            , process_element(*this)
            , is_block(*this)
            {}
    };

    void quickbook_grammar::impl::init_main()
    {
        main_grammar_local& local = cleanup_.add(
            new main_grammar_local(actions));

        block_skip_initial_spaces =
            *(cl::blank_p | comment) >> block_start
            ;

        block_start =
            local.top_level >> blank
            ;

        local.top_level =
            actions.scoped_context(element_info::in_block)
            [   local.blocks
            >>  *(  local.element
                >>  !(cl::eps_p(local.is_block) >> +eol >> local.blocks)
                |   local.paragraph_separator >> local.blocks
                |   common
                |   cl::space_p                 [actions.space_char]
                |   cl::anychar_p               [actions.plain_char]
                )
            ]
            ;

        local.blocks =
           *(   local.code
            |   local.list
            |   local.hr
            |   +eol
            )
            ;

        local.paragraph_separator
            =   cl::eol_p
            >> *cl::blank_p
            >>  cl::eol_p                       [actions.paragraph]
            ;

        local.hr =
                cl::str_p("----")
            >>  actions.values.list(block_tags::hr)
                [   *(cl::anychar_p - eol)
                >>  +eol
                ]                               [actions.element]
            ;

        local.element
            =   '['
            >>  (   cl::eps_p(cl::punct_p)
                >>  elements                    [ph::var(local.info) = ph::arg1]
                |   elements                    [ph::var(local.info) = ph::arg1]
                >>  (cl::eps_p - (cl::alnum_p | '_'))
                )
            >>  local.process_element()
                [   actions.values.list(ph::var(local.info.tag))
                    [   cl::lazy_p(*ph::var(local.info.rule))
                    >>  space
                    >>  ']'
                    ]                           [actions.element]
                ]
            ;

        local.code =
            (
                local.code_line
                >> *(*local.blank_line >> local.code_line)
            )                                   [actions.code]
            >> *eol
            ;

        local.code_line =
            cl::blank_p >> *(cl::anychar_p - cl::eol_p) >> cl::eol_p
            ;

        local.blank_line =
            *cl::blank_p >> cl::eol_p
            ;

        local.list =
                cl::eps_p(cl::ch_p('*') | '#')
                                            [actions.values.reset()]
            >>  actions.scoped_output()
                [
                actions.values.list(block_tags::list)
                [   +actions.values.list()
                    [   (*cl::blank_p)      [actions.values.entry(ph::arg1, ph::arg2, general_tags::list_indent)]
                    >>  (cl::ch_p('*') | '#')
                                            [actions.values.entry(ph::arg1, ph::arg2, general_tags::list_mark)]
                    >>  *cl::blank_p
                    >>  local.list_item     [actions.to_value]
                    ]
                ]
                ]                           [actions.element]
            ;

        local.list_item =
            actions.scoped_context(element_info::in_phrase)
            [
            actions.values.save()
            [
                *(  common
                |   (cl::anychar_p -
                        (   cl::eol_p >> *cl::blank_p
                        >>  (cl::ch_p('*') | '#' | cl::eol_p)
                        )
                    )                       [actions.plain_char]
                )
            ]
            ]
            >> +eol
            ;

        common =
                local.macro
            |   local.element
            |   local.template_
            |   local.break_
            |   local.code_block
            |   local.inline_code
            |   local.simple_markup
            |   local.escape
            |   comment
            ;

        local.macro =
            // must not be followed by alpha or underscore
            cl::eps_p(actions.macro
                >> (cl::eps_p - (cl::alpha_p | '_')))
            >> actions.macro                    [actions.do_macro]
            ;

        local.template_ =
            (   '['
            >>  space
            >>  actions.values.list(template_tags::template_)
                [   !cl::str_p("`")             [actions.values.entry(ph::arg1, ph::arg2, template_tags::escape)]
                >>  (   cl::eps_p(cl::punct_p)
                    >>  actions.templates.scope [actions.values.entry(ph::arg1, ph::arg2, template_tags::identifier)]
                    |   actions.templates.scope [actions.values.entry(ph::arg1, ph::arg2, template_tags::identifier)]
                    >>  cl::eps_p(hard_space)
                    )
                >>  space
                >>  !local.template_args
                >>  ']'
                ]
            )                                   [actions.element]
            ;

        local.template_args =
                cl::eps_p(qbk_since(105u))
            >>  local.template_args_1_5
            |   cl::eps_p(qbk_before(105u))
            >>  local.template_args_1_4
            ;

        local.template_args_1_4 = local.template_arg_1_4 >> *(".." >> local.template_arg_1_4);

        local.template_arg_1_4 =
            (   cl::eps_p(*cl::blank_p >> cl::eol_p)
            >>  local.template_inner_arg_1_4    [actions.values.entry(ph::arg1, ph::arg2, template_tags::block)]
            |   local.template_inner_arg_1_4    [actions.values.entry(ph::arg1, ph::arg2, template_tags::phrase)]
            )                               
            ;

        local.template_inner_arg_1_4 =
            +(local.brackets_1_4 | (cl::anychar_p - (cl::str_p("..") | ']')))
            ;

        local.brackets_1_4 =
            '[' >> local.template_inner_arg_1_4 >> ']'
            ;

        local.template_args_1_5 = local.template_arg_1_5 >> *(".." >> local.template_arg_1_5);

        local.template_arg_1_5 =
            (   cl::eps_p(*cl::blank_p >> cl::eol_p)
            >>  local.template_arg_1_5_content  [actions.values.entry(ph::arg1, ph::arg2, template_tags::block)]
            |   local.template_arg_1_5_content  [actions.values.entry(ph::arg1, ph::arg2, template_tags::phrase)]
            )
            ;

        local.template_arg_1_5_content =
            +(local.brackets_1_5 | ('\\' >> cl::anychar_p) | (cl::anychar_p - (cl::str_p("..") | '[' | ']')))
            ;

        local.template_inner_arg_1_5 =
            +(local.brackets_1_5 | ('\\' >> cl::anychar_p) | (cl::anychar_p - (cl::str_p('[') | ']')))
            ;

        local.brackets_1_5 =
            '[' >> local.template_inner_arg_1_5 >> ']'
            ;

        local.break_
            =   (   '['
                >>  space
                >>  "br"
                >>  space
                >>  ']'
                )                               [actions.break_]
                ;

        local.inline_code =
            '`' >>
            (
               *(cl::anychar_p -
                    (   '`'
                    |   (cl::eol_p >> *cl::blank_p >> cl::eol_p)
                                                // Make sure that we don't go
                    )                           // past a single block
                ) >> cl::eps_p('`')
            )                                   [actions.inline_code]
            >>  '`'
            ;

        local.code_block =
                (
                    "```" >>
                    (
                       *(cl::anychar_p - "```")
                            >> cl::eps_p("```")
                    )                           [actions.code_block]
                    >>  "```"
                )
            |   (
                    "``" >>
                    (
                       *(cl::anychar_p - "``")
                            >> cl::eps_p("``")
                    )                           [actions.code_block]
                    >>  "``"
                )
            ;

        local.simple_markup =
                cl::chset<>("*/_=")             [local.simple_markup.mark = ph::arg1]
            >>  cl::eps_p(cl::graph_p)          // graph_p must follow first mark
            >>  lookback
                [   cl::anychar_p               // skip back over the markup
                >>  ~cl::eps_p(cl::f_ch_p(local.simple_markup.mark))
                                                // first mark not be preceeded by
                                                // the same character.
                >>  (cl::space_p | cl::punct_p | cl::end_p)
                                                // first mark must be preceeded
                                                // by space or punctuation or the
                                                // mark character or a the start.
                ]
            >>  actions.values.save()
                [
                    actions.scoped_output()
                    [
                        (   cl::eps_p(actions.macro >> local.simple_markup_end)
                        >>  actions.macro       [actions.do_macro]
                        |   ~cl::eps_p(cl::f_ch_p(local.simple_markup.mark))
                        >>  +(  ~cl::eps_p
                                (   lookback [~cl::f_ch_p(local.simple_markup.mark)]
                                >>  local.simple_markup_end
                                )
                            >>  cl::anychar_p   [actions.plain_char]
                            )
                        )                       [actions.to_value]
                    ]
                >>  cl::f_ch_p(local.simple_markup.mark)
                                                [actions.simple_markup]
                ]
            ;

        local.simple_markup_end
            =   (   lookback[cl::graph_p]       // final mark must be preceeded by
                                                // graph_p
                >>  cl::f_ch_p(local.simple_markup.mark)
                >>  ~cl::eps_p(cl::f_ch_p(local.simple_markup.mark))
                                                // final mark not be followed by
                                                // the same character.
                >>  (cl::space_p | cl::punct_p | cl::end_p)
                                                 // final mark must be followed by
                                                 // space or punctuation
                )
            |   '['
            |   "'''"
            |   '`'
            |   phrase_end
                ;

        phrase =
            actions.scoped_context(element_info::in_phrase)
            [
            actions.values.save()
            [   *(  common
                |   (cl::anychar_p - phrase_end)
                                                [actions.plain_char]
                )
            ]
            ]
            ;

        extended_phrase =
            actions.scoped_context(element_info::in_conditional)
            [
            actions.values.save()
            [  *(   common
                |   (cl::anychar_p - phrase_end)
                                                [actions.plain_char]
                )
            ]
            ]
            ;

        inside_paragraph =
            actions.scoped_context(element_info::in_nested_block)
            [
            actions.values.save()
            [   *(  local.paragraph_separator   [actions.paragraph]
                |   common
                |   (cl::anychar_p - phrase_end)
                                                [actions.plain_char]
                )
            ]                                   [actions.paragraph]
            ]
            ;

        local.escape =
                cl::str_p("\\n")                [actions.break_]
            |   cl::str_p("\\ ")                // ignore an escaped space
            |   '\\' >> cl::punct_p             [actions.plain_char]
            |   "\\u" >> cl::repeat_p(4) [cl::chset<>("0-9a-fA-F")]
                                                [actions.escape_unicode]
            |   "\\U" >> cl::repeat_p(8) [cl::chset<>("0-9a-fA-F")]
                                                [actions.escape_unicode]
            |   ("'''" >> !eol)
            >>  actions.values.save()
                [   (*(cl::anychar_p - "'''"))  [actions.values.entry(ph::arg1, ph::arg2, phrase_tags::escape)]
                >>  (   cl::str_p("'''")
                    |   cl::eps_p               [actions.error("Unclosed boostbook escape.")]
                    )                           [actions.element]
                ]
            ;

        //
        // Simple phrase grammar
        //

        simple_phrase =
            actions.scoped_context(element_info::in_phrase)
            [
            actions.values.save()
            [
           *(   common
            |   (cl::anychar_p - ']')           [actions.plain_char]
            )
            ]
            ]
            ;

        //
        // Command line
        //

        command_line =
            actions.values.list(block_tags::macro_definition)
            [   *cl::space_p
            >>  local.command_line_macro_identifier
                                                [actions.values.entry(ph::arg1, ph::arg2)]
            >>  *cl::space_p
            >>  (   '='
                >>  *cl::space_p
                >>  local.command_line_phrase
                >>  *cl::space_p
                |   cl::eps_p
                )                               [actions.to_value]
            ]                                   [actions.element]
            ;

        local.command_line_macro_identifier =
            +(cl::anychar_p - (cl::space_p | ']' | '='))
            ;


        local.command_line_phrase =
            actions.scoped_context(element_info::in_phrase)
            [
            actions.values.save()
            [   *(   common
                |   (cl::anychar_p - ']')       [actions.plain_char]
                )
            ]
            ]
            ;

        // Miscellaneous stuff

        // Follows an alphanumeric identifier - ensures that it doesn't
        // match an empty space in the middle of the identifier.
        hard_space =
            (cl::eps_p - (cl::alnum_p | '_')) >> space
            ;

        space =
            *(cl::space_p | comment)
            ;

        blank =
            *(cl::blank_p | comment)
            ;

        eol = blank >> cl::eol_p
            ;

        phrase_end =
                ']'
            |   cl::eps_p(ph::var(actions.no_eols))
            >>  cl::eol_p >> *cl::blank_p >> cl::eol_p
            ;                                   // Make sure that we don't go
                                                // past a single block, except
                                                // when preformatted.

        comment =
            "[/" >> *(local.dummy_block | (cl::anychar_p - ']')) >> ']'
            ;

        local.dummy_block =
            '[' >> *(local.dummy_block | (cl::anychar_p - ']')) >> ']'
            ;

        macro_identifier =
            +(cl::anychar_p - (cl::space_p | ']'))
            ;

    }
}
