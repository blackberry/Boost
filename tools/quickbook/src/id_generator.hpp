/*=============================================================================
    Copyright (c) 2011 Daniel James

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#if !defined(BOOST_QUICKBOOK_ID_GENERATOR_HPP)
#define BOOST_QUICKBOOK_ID_GENERATOR_HPP

#include "fwd.hpp"
#include <boost/unordered/unordered_map.hpp>
#include <boost/shared_ptr.hpp>
#include <deque>
#include <string>

namespace quickbook
{
    struct string_ref;

    struct id_generator
    {
    public:

        enum categories
        {
            explicit_id = 0,    // Explicitly given by user
            generated_doc,      // Generated ids for document.
            generated_section,  // Generated ids for sections.
            generated_heading,  // Generated ids for headings.
            generated,          // Generated ids for other elements.
            numbered,           // Just used to avoid random docbook ids
            default_category
        };

    private:

        struct placeholder_id;
        struct id_data;
        struct id_generation_data;

        struct placeholder_id
        {
            placeholder_id(id_generator::categories category, id_data* data)
              : category(category),
                data(data),
                final_id() {}

            id_generator::categories category;
            id_data* data;
            std::string final_id;
            
        };

        struct id_data
        {
            id_data(std::string const& name,
                    id_generator::categories category,
                    bool used = false)
              : name(name),
                category(category),
                used(used),
                generation_data() {}
            
            std::string name;
            id_generator::categories category;
            bool used;
            boost::shared_ptr<id_generation_data> generation_data;
        };
        
        struct id_generation_data
        {
            id_generation_data(std::string const& parent, std::string const& base)
              : parent(parent),
                base(base),
                needs_underscore(false),
                count(0)
            {
                new_base_value();
            }

            void new_base_value();

            std::string parent;
            std::string base;
            bool needs_underscore;
            int count;
        };

        boost::unordered_map<std::string, id_data> ids;
        std::deque<placeholder_id> placeholders;

    public:
        id_generator();
        ~id_generator();

        std::string add(std::string const& id, categories priority);

        std::string replace_placeholders(std::string const&);
        string_ref get(string_ref placeholder);

    private:
        id_generator(id_generator const&);
        id_generator& operator=(id_generator const&);

        void generate_id(placeholder_id*);
        bool try_potential_id(placeholder_id*);
        bool try_counted_id(placeholder_id*);
    };
}

#endif