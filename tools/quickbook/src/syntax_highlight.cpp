/*=============================================================================
    Copyright (c) 2002 2004 2006 Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#include <boost/spirit/include/classic_core.hpp>
#include <boost/spirit/include/classic_confix.hpp>
#include <boost/spirit/include/classic_chset.hpp>
#include <boost/spirit/include/classic_symbols.hpp>
#include <boost/spirit/include/classic_loops.hpp>
#include "grammar.hpp"
#include "grammar_impl.hpp" // Just for context stuff. Should move?
#include "actions_class.hpp"

namespace quickbook
{    
    namespace cl = boost::spirit::classic;

    // Grammar for C++ highlighting
    struct cpp_highlight
    : public cl::grammar<cpp_highlight>
    {
        cpp_highlight(collector& out, actions& escape_actions)
        : out(out), escape_actions(escape_actions) {}

        template <typename Scanner>
        struct definition
        {
            definition(cpp_highlight const& self)
                : g(self.escape_actions.grammar())
            {
                program
                    =
                    *(  (+cl::space_p)  [space(self.out)]
                    |   macro
                    |   escape
                    |   preprocessor    [span("preprocessor", self.out)]
                    |   comment
                    |   keyword         [span("keyword", self.out)]
                    |   identifier      [span("identifier", self.out)]
                    |   special         [span("special", self.out)]
                    |   string_         [span("string", self.out)]
                    |   char_           [span("char", self.out)]
                    |   number          [span("number", self.out)]
                    |   cl::repeat_p(1)[cl::anychar_p]
                                        [unexpected_char(self.out, self.escape_actions)]
                    )
                    ;

                macro =
                    // must not be followed by alpha or underscore
                    cl::eps_p(self.escape_actions.macro
                        >> (cl::eps_p - (cl::alpha_p | '_')))
                    >> self.escape_actions.macro        [do_macro_action(self.out, self.escape_actions)]
                    ;

                qbk_phrase =
                    self.escape_actions.scoped_context(element_info::in_phrase)
                    [  *(   g.common
                        |   (cl::anychar_p - cl::str_p("``"))
                                        [self.escape_actions.plain_char]
                        )
                    ]
                    ;

                escape =
                    cl::str_p("``")     [pre_escape_back(self.escape_actions, save)]
                    >>
                    (
                        (
                            (
                                (+(cl::anychar_p - "``") >> cl::eps_p("``"))
                                & qbk_phrase
                            )
                            >>  cl::str_p("``")
                        )
                        |
                        (
                            cl::eps_p   [self.escape_actions.error]
                            >> *cl::anychar_p
                        )
                    )                   [post_escape_back(self.out, self.escape_actions, save)]
                    ;

                preprocessor
                    =   '#' >> *cl::space_p >> ((cl::alpha_p | '_') >> *(cl::alnum_p | '_'))
                    ;

                comment
                    =   cl::str_p("//")         [span_start("comment", self.out)]
                    >>  *(  escape
                        |   (+(cl::anychar_p - (cl::eol_p | "``")))
                                                [span(0, self.out)]
                        )
                    >>  cl::eps_p               [span_end(self.out)]
                    |   cl::str_p("/*")         [span_start("comment", self.out)]
                    >>  *(  escape
                        |   (+(cl::anychar_p - (cl::str_p("*/") | "``")))
                                                [span(0, self.out)]
                        )
                    >>  (!cl::str_p("*/"))      [span_end(self.out)]
                    ;

                keyword
                    =   keyword_ >> (cl::eps_p - (cl::alnum_p | '_'))
                    ;   // make sure we recognize whole words only

                keyword_
                    =   "and_eq", "and", "asm", "auto", "bitand", "bitor",
                        "bool", "break", "case", "catch", "char", "class",
                        "compl", "const_cast", "const", "continue", "default",
                        "delete", "do", "double", "dynamic_cast",  "else",
                        "enum", "explicit", "export", "extern", "false",
                        "float", "for", "friend", "goto", "if", "inline",
                        "int", "long", "mutable", "namespace", "new", "not_eq",
                        "not", "operator", "or_eq", "or", "private",
                        "protected", "public", "register", "reinterpret_cast",
                        "return", "short", "signed", "sizeof", "static",
                        "static_cast", "struct", "switch", "template", "this",
                        "throw", "true", "try", "typedef", "typeid",
                        "typename", "union", "unsigned", "using", "virtual",
                        "void", "volatile", "wchar_t", "while", "xor_eq", "xor"
                    ;

                special
                    =   +cl::chset_p("~!%^&*()+={[}]:;,<.>?/|\\-")
                    ;

                string_char = ('\\' >> cl::anychar_p) | (cl::anychar_p - '\\');

                string_
                    =   !cl::as_lower_d['l'] >> cl::confix_p('"', *string_char, '"')
                    ;

                char_
                    =   !cl::as_lower_d['l'] >> cl::confix_p('\'', *string_char, '\'')
                    ;

                number
                    =   (
                            cl::as_lower_d["0x"] >> cl::hex_p
                        |   '0' >> cl::oct_p
                        |   cl::real_p
                        )
                        >>  *cl::as_lower_d[cl::chset_p("ldfu")]
                    ;

                identifier
                    =   (cl::alpha_p | '_') >> *(cl::alnum_p | '_')
                    ;
            }

            cl::rule<Scanner>
                            program, macro, preprocessor, comment, special, string_, 
                            char_, number, identifier, keyword, qbk_phrase, escape,
                            string_char;

            cl::symbols<> keyword_;
            quickbook_grammar& g;
            std::string save;

            cl::rule<Scanner> const&
            start() const { return program; }
        };

        collector& out;
        actions& escape_actions;
    };

    // Grammar for Python highlighting
    // See also: The Python Reference Manual
    // http://docs.python.org/ref/ref.html
    struct python_highlight
    : public cl::grammar<python_highlight>
    {
        python_highlight(collector& out, actions& escape_actions)
        : out(out), escape_actions(escape_actions) {}

        template <typename Scanner>
        struct definition
        {
            definition(python_highlight const& self)
                : g(self.escape_actions.grammar())
            {
                program
                    =
                    *(  (+cl::space_p)  [space(self.out)]
                    |   macro
                    |   escape          
                    |   comment
                    |   keyword         [span("keyword", self.out)]
                    |   identifier      [span("identifier", self.out)]
                    |   special         [span("special", self.out)]
                    |   string_         [span("string", self.out)]
                    |   number          [span("number", self.out)]
                    |   cl::repeat_p(1)[cl::anychar_p]
                                        [unexpected_char(self.out, self.escape_actions)]
                    )
                    ;

                macro = 
                    // must not be followed by alpha or underscore
                    cl::eps_p(self.escape_actions.macro
                        >> (cl::eps_p - (cl::alpha_p | '_')))
                    >> self.escape_actions.macro        [do_macro_action(self.out, self.escape_actions)]
                    ;

                qbk_phrase =
                    self.escape_actions.scoped_context(element_info::in_phrase)
                    [
                       *(   g.common
                        |   (cl::anychar_p - cl::str_p("``"))
                                        [self.escape_actions.plain_char]
                        )
                    ]
                    ;

                escape =
                    cl::str_p("``")     [pre_escape_back(self.escape_actions, save)]
                    >>
                    (
                        (
                            (
                                (+(cl::anychar_p - "``") >> cl::eps_p("``"))
                                & qbk_phrase
                            )
                            >>  cl::str_p("``")
                        )
                        |
                        (
                            cl::eps_p   [self.escape_actions.error]
                            >> *cl::anychar_p
                        )
                    )                   [post_escape_back(self.out, self.escape_actions, save)]
                    ;

                comment
                    =   cl::str_p("#")          [span_start("comment", self.out)]
                    >>  *(  escape
                        |   (+(cl::anychar_p - (cl::eol_p | "``")))
                                                [span(0, self.out)]
                        )
                    >>  cl::eps_p               [span_end(self.out)]
                    ;

                keyword
                    =   keyword_ >> (cl::eps_p - (cl::alnum_p | '_'))
                    ;   // make sure we recognize whole words only

                keyword_
                    =
                    "and",       "del",       "for",       "is",        "raise",    
                    "assert",    "elif",      "from",      "lambda",    "return",   
                    "break",     "else",      "global",    "not",       "try",  
                    "class",     "except",    "if",        "or",        "while",    
                    "continue",  "exec",      "import",    "pass",      "yield",   
                    "def",       "finally",   "in",        "print",

                    // Technically "as" and "None" are not yet keywords (at Python
                    // 2.4). They are destined to become keywords, and we treat them 
                    // as such for syntax highlighting purposes.
                    
                    "as", "None"
                    ;

                special
                    =   +cl::chset_p("~!%^&*()+={[}]:;,<.>/|\\-")
                    ;

                string_prefix
                    =    cl::as_lower_d[cl::str_p("u") >> ! cl::str_p("r")]
                    ;
                
                string_
                    =   ! string_prefix >> (long_string | short_string)
                    ;

                string_char = ('\\' >> cl::anychar_p) | (cl::anychar_p - '\\');
            
                short_string
                    =   cl::confix_p('\'', * string_char, '\'') |
                        cl::confix_p('"', * string_char, '"')
                    ;
            
                long_string
                    // Note: the "cl::str_p" on the next two lines work around
                    // an INTERNAL COMPILER ERROR when using VC7.1
                    =   cl::confix_p(cl::str_p("'''"), * string_char, "'''") |
                        cl::confix_p(cl::str_p("\"\"\""), * string_char, "\"\"\"")
                    ;
                
                number
                    =   (
                            cl::as_lower_d["0x"] >> cl::hex_p
                        |   '0' >> cl::oct_p
                        |   cl::real_p
                        )
                        >>  *cl::as_lower_d[cl::chset_p("lj")]
                    ;

                identifier
                    =   (cl::alpha_p | '_') >> *(cl::alnum_p | '_')
                    ;
            }

            cl::rule<Scanner>
                            program, macro, comment, special, string_, string_prefix, 
                            short_string, long_string, number, identifier, keyword, 
                            qbk_phrase, escape, string_char;

            cl::symbols<> keyword_;
            quickbook_grammar& g;
            std::string save;

            cl::rule<Scanner> const&
            start() const { return program; }
        };

        collector& out;
        actions& escape_actions;
    };

    // Grammar for plain text (no actual highlighting)
    struct teletype_highlight
    : public cl::grammar<teletype_highlight>
    {
        teletype_highlight(collector& out, actions& escape_actions)
        : out(out), escape_actions(escape_actions) {}

        template <typename Scanner>
        struct definition
        {
            definition(teletype_highlight const& self)
                : g(self.escape_actions.grammar())
            {
                program
                    =
                    *(  macro
                    |   escape          
                    |   cl::repeat_p(1)[cl::anychar_p]  [plain_char_action(self.out, self.escape_actions)]
                    )
                    ;

                macro =
                    // must not be followed by alpha or underscore
                    cl::eps_p(self.escape_actions.macro
                        >> (cl::eps_p - (cl::alpha_p | '_')))
                    >> self.escape_actions.macro        [do_macro_action(self.out, self.escape_actions)]
                    ;

                qbk_phrase =
                    self.escape_actions.scoped_context(element_info::in_phrase)
                    [
                       *(   g.common
                        |   (cl::anychar_p - cl::str_p("``"))
                                        [self.escape_actions.plain_char]
                        )
                    ]
                    ;

                escape =
                    cl::str_p("``")     [pre_escape_back(self.escape_actions, save)]
                    >>
                    (
                        (
                            (
                                (+(cl::anychar_p - "``") >> cl::eps_p("``"))
                                & qbk_phrase
                            )
                            >>  cl::str_p("``")
                        )
                        |
                        (
                            cl::eps_p   [self.escape_actions.error]
                            >> *cl::anychar_p
                        )
                    )                   [post_escape_back(self.out, self.escape_actions, save)]
                    ;
            }

            cl::rule<Scanner> program, macro, qbk_phrase, escape;

            quickbook_grammar& g;
            std::string save;

            cl::rule<Scanner> const&
            start() const { return program; }
        };

        collector& out;
        actions& escape_actions;
    };

    std::string syntax_highlight(
        iterator first, iterator last,
        actions& escape_actions,
        std::string const& source_mode)
    {
        quickbook::collector temp;

        // print the code with syntax coloring
        if (source_mode == "c++")
        {
            cpp_highlight cpp_p(temp, escape_actions);
            boost::spirit::classic::parse(first, last, cpp_p);
        }
        else if (source_mode == "python")
        {
            python_highlight python_p(temp, escape_actions);
            boost::spirit::classic::parse(first, last, python_p);
        }
        else if (source_mode == "teletype")
        {
            teletype_highlight teletype_p(temp, escape_actions);
            boost::spirit::classic::parse(first, last, teletype_p);
        }
        else
        {
            BOOST_ASSERT(0);
        }

        std::string str;
        temp.swap(str);
        
        return str;
    }
}
