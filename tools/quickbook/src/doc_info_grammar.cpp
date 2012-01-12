/*=============================================================================
    Copyright (c) 2002 2004 2006 Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#include <map>
#include <boost/foreach.hpp>
#include <boost/spirit/include/classic_core.hpp>
#include <boost/spirit/include/classic_actor.hpp>
#include <boost/spirit/include/classic_loops.hpp>
#include <boost/spirit/include/classic_symbols.hpp>
#include <boost/spirit/include/classic_chset.hpp>
#include <boost/spirit/include/classic_numerics.hpp>
#include <boost/spirit/include/phoenix1_primitives.hpp>
#include "grammar_impl.hpp"
#include "actions_class.hpp"
#include "doc_info_tags.hpp"
#include "phrase_tags.hpp"

namespace quickbook
{
    namespace cl = boost::spirit::classic;

    struct attribute_info
    {
        attribute_info(value::tag_type t, cl::rule<scanner>* r)
            : tag(t), rule(r)
        {}

        value::tag_type tag;
        cl::rule<scanner>* rule;
    };

    struct doc_info_grammar_local
    {
        struct assign_attribute_type
        {
            assign_attribute_type(doc_info_grammar_local& l)
                : l(l)
            {}

            void operator()(value::tag_type& t) const {
                l.attribute_rule = *l.attribute_rules[t];
                l.attribute_tag = t;
            }
            
            doc_info_grammar_local& l;
        };
        
        struct fallback_attribute_type
        {
            fallback_attribute_type(doc_info_grammar_local& l)
                : l(l)
            {}

            void operator()(iterator, iterator) const {
                l.attribute_rule = l.doc_fallback;
                l.attribute_tag = value::default_tag;
            }
            
            doc_info_grammar_local& l;
        };

        cl::rule<scanner>
                        doc_title, doc_simple, doc_phrase, doc_fallback,
                        doc_authors, doc_author,
                        doc_copyright, doc_copyright_holder,
                        doc_source_mode, doc_biblioid,
                        quickbook_version, char_;
        cl::uint_parser<int, 10, 4, 4> doc_copyright_year;
        cl::symbols<> doc_types;
        cl::symbols<value::tag_type> doc_attributes;
        std::map<value::tag_type, cl::rule<scanner>* > attribute_rules;
        value::tag_type attribute_tag;
        cl::rule<scanner> attribute_rule;
        assign_attribute_type assign_attribute;
        fallback_attribute_type fallback_attribute;
        
        doc_info_grammar_local()
            : assign_attribute(*this)
            , fallback_attribute(*this)
        {}
    };

    void quickbook_grammar::impl::init_doc_info()
    {
        doc_info_grammar_local& local = cleanup_.add(
            new doc_info_grammar_local);

        typedef cl::uint_parser<int, 10, 1, 2>  uint2_t;

        local.doc_types =
            "book", "article", "library", "chapter", "part"
          , "appendix", "preface", "qandadiv", "qandaset"
          , "reference", "set"
        ;

        BOOST_FOREACH(value::tag_type t, doc_info_attributes::tags()) {
            local.doc_attributes.add(doc_info_attributes::name(t), t);
        }
        
        doc_info_details =
            space
            >> '[' >> space
            >> (local.doc_types >> cl::eps_p)
                                            [actions.values.reset()]
                                            [actions.values.entry(ph::arg1, ph::arg2, doc_info_tags::type)]
            >> hard_space
            >>  (  *(~cl::eps_p(cl::ch_p('[') | ']' | cl::eol_p) >> local.char_)
                )                           [actions.docinfo_value(ph::arg1, ph::arg2, doc_info_tags::title)]
            >>  !(
                    space >> '[' >>
                        local.quickbook_version
                    >> space >> ']'
                )
            >>  *(
                    space
                >>  '['
                >>  space
                >>  (   local.doc_attributes
                                            [local.assign_attribute]
                    |   (+(cl::alnum_p | '_' | '-'))
                                            [local.fallback_attribute]
                                            [actions.error("Unrecognized document attribute: '%s'.")]
                    )
                >>  hard_space
                >>  actions.values.list(ph::var(local.attribute_tag))
                    [local.attribute_rule]
                >>  space
                >>  ']'
                >>  +cl::eol_p
                )
            >>  space                       [actions.values.sort()]
            >>  ']'
            >>  +cl::eol_p
            ;

        local.quickbook_version =
            actions.values.list(doc_info_tags::qbk_version)
            [   "quickbook"
            >>  hard_space
            >>  (   cl::uint_p              [actions.values.entry(ph::arg1)]
                    >> '.' 
                    >>  uint2_t()           [actions.values.entry(ph::arg1)]
                )
            ]
            ;

        // TODO: Clear phrase afterwards?

        local.doc_fallback = (*(~cl::eps_p(']') >> local.char_));

        // TODO: Restrictions on doc_id and doc_dirname?

        local.doc_simple = (*(~cl::eps_p(']') >> local.char_)) [actions.docinfo_value(ph::arg1, ph::arg2)];
        local.attribute_rules[doc_info_attributes::version] = &local.doc_simple;
        local.attribute_rules[doc_info_attributes::id] = &local.doc_simple;
        local.attribute_rules[doc_info_attributes::dirname] = &local.doc_simple;
        local.attribute_rules[doc_info_attributes::category] = &local.doc_simple;
        local.attribute_rules[doc_info_attributes::last_revision] = &local.doc_simple;
        local.attribute_rules[doc_info_attributes::lang] = &local.doc_simple;

        local.doc_copyright_holder
            =   *(  ~cl::eps_p
                    (   ']'
                    |   ',' >> space >> local.doc_copyright_year
                    )
                >>  local.char_
                );

        local.doc_copyright =
            *(  +(  local.doc_copyright_year
                                            [actions.values.entry(ph::arg1, doc_info_tags::copyright_year)]
                >>  space
                >>  !(  '-'
                    >>  space
                    >>  local.doc_copyright_year
                                            [actions.values.entry(ph::arg1, doc_info_tags::copyright_year_end)]
                    >>  space
                    )
                >>  !cl::ch_p(',')
                >>  space
                )
            >>  local.doc_copyright_holder  [actions.docinfo_value(ph::arg1, ph::arg2, doc_info_tags::copyright_name)]
            >>  !cl::ch_p(',')
            >>  space
            )
            ;

        local.attribute_rules[doc_info_attributes::copyright] = &local.doc_copyright;

        local.doc_phrase = simple_phrase [actions.docinfo_value(ph::arg1, ph::arg2)];
        local.attribute_rules[doc_info_attributes::purpose] = &local.doc_phrase;
        local.attribute_rules[doc_info_attributes::license] = &local.doc_phrase;

        local.doc_author =
                '['
            >>   space
            >>  (*(~cl::eps_p(',') >> local.char_))
                                            [actions.docinfo_value(ph::arg1, ph::arg2, doc_info_tags::author_surname)]
            >>  ',' >> space
            >>  (*(~cl::eps_p(']') >> local.char_))
                                            [actions.docinfo_value(ph::arg1, ph::arg2, doc_info_tags::author_first)]
            >>  ']'
            ;

        local.doc_authors =
            *(  local.doc_author
            >>  space
            >>  !(cl::ch_p(',') >> space)
            )
            ;

        local.attribute_rules[doc_info_attributes::authors] = &local.doc_authors;

        local.doc_source_mode =
                (
                   cl::str_p("c++") 
                |  "python"
                |  "teletype"
                )                           [cl::assign_a(actions.source_mode)]
            ;

        local.attribute_rules[doc_info_attributes::source_mode] = &local.doc_source_mode;

        local.doc_biblioid =
                (+cl::alnum_p)              [actions.values.entry(ph::arg1, ph::arg2, doc_info_tags::biblioid_class)]
            >>  hard_space
            >>  (+(~cl::eps_p(']') >> local.char_))
                                            [actions.docinfo_value(ph::arg1, ph::arg2, doc_info_tags::biblioid_value)]
            ;

        local.attribute_rules[doc_info_attributes::biblioid] = &local.doc_biblioid;

        local.char_ =
                cl::str_p("\\n")            [actions.break_]
            |   "\\ "                       // ignore an escaped space
            |   '\\' >> cl::punct_p         [actions.plain_char]
            |   "\\u" >> cl::repeat_p(4)
                    [cl::chset<>("0-9a-fA-F")]
                                            [actions.escape_unicode]
            |   "\\U" >> cl::repeat_p(8)
                    [cl::chset<>("0-9a-fA-F")]
                                            [actions.escape_unicode]
            |   ("'''" >> !eol)
            >>  actions.values.save()
                [  (*(cl::anychar_p - "'''"))
                                            [actions.values.entry(ph::arg1, ph::arg2, phrase_tags::escape)]
                >>  cl::str_p("'''")        [actions.element]
                ]
            |   cl::anychar_p               [actions.plain_char]
            ;
    }
}
