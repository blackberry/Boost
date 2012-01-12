/*=============================================================================
    Copyright (c) 2011 Daniel James

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#include "id_generator.hpp"
#include "markups.hpp"
#include "phrase_tags.hpp"
#include <cctype>
#include <boost/lexical_cast.hpp>
#include <algorithm>
#include <vector>

namespace quickbook
{
    // string_ref

    struct string_ref
    {
    public:
        typedef std::string::const_iterator iterator;

    private:
        iterator begin_, end_;

    public:
        string_ref() : begin_(), end_() {}

        explicit string_ref(iterator b, iterator e)
            : begin_(b), end_(e) {}

        explicit string_ref(std::string const& x)
            : begin_(x.begin()), end_(x.end()) {}

        iterator begin() const { return begin_; }
        iterator end() const { return end_; }
        
        std::size_t size() const
        {
            return static_cast<std::size_t>(end_ - begin_);
        }    
    };

    bool operator==(string_ref const& x, string_ref const& y);
    bool operator<(string_ref const& x, string_ref const& y);

    inline bool operator==(string_ref const& x, std::string const& y)
    {
        return x == string_ref(y);
    }

    inline bool operator==(std::string const& x, string_ref const& y)
    {
        return string_ref(x) == y;
    }

    inline bool operator<(string_ref const& x, std::string const& y)
    {
        return x < string_ref(y);
    }

    inline bool operator<(std::string const& x, string_ref const& y)
    {
        return string_ref(x) < y;
    }

    bool operator==(string_ref const& x, string_ref const& y)
    {
        return x.size() == y.size() &&
            std::equal(x.begin(), x.end(), y.begin());
    }

    bool operator<(string_ref const& x, string_ref const& y)
    {
        return std::lexicographical_compare(
            x.begin(), x.end(), y.begin(), y.end());
    }

    //
    // id_generator
    //

    static const std::size_t max_size = 32;

    namespace
    {
        std::string normalize_id(std::string const& id)
        {
            std::string result;

            std::string::const_iterator it = id.begin();
            while (it != id.end()) {
                if (*it == '_') {
                    do {
                        ++it;
                    } while(it != id.end() && *it == '_');

                    if (it != id.end()) result += '_';
                }
                else {
                    result += *it;
                    ++it;
                }
            }
            
            return result;
        }
    }

    id_generator::id_generator()
    {
    }

    id_generator::~id_generator()
    {
    }

    std::string id_generator::add(
            std::string const& value,
            id_generator::categories category)
    {
        std::string result;

        id_data& data = ids.emplace(boost::unordered::piecewise_construct,
            boost::make_tuple(value),
            boost::make_tuple(value, category)).first->second;

        // Doesn't check if explicit ids collide, could probably be a warning.
        if (category == explicit_id)
        {
            data.category = category;
            data.used = true;
            result = value;
        }
        else
        {
            if (category < data.category) data.category = category;

            // '$' can't appear in quickbook ids, so use it indicate a
            // placeholder id.
            result = "$" +
                boost::lexical_cast<std::string>(placeholders.size());
            placeholders.push_back(placeholder_id(category, &data));
        }

        return result;
    }

    string_ref id_generator::get(string_ref value)
    {
        // If this isn't a placeholder id. 
        if (value.size() <= 1 || *value.begin() != '$')
            return value;

        placeholder_id* placeholder = &placeholders.at(
            boost::lexical_cast<int>(std::string(
                value.begin() + 1, value.end())));

        if (placeholder->final_id.empty())
        {
            if (placeholder->category < id_generator::numbered &&
                    !placeholder->data->used &&
                    placeholder->data->category == placeholder->category)
            {
                placeholder->data->used = true;
                placeholder->final_id = placeholder->data->name;
            }
            else
            {
                generate_id(placeholder);
            }
        }

        return string_ref(placeholder->final_id);
    }

    void id_generator::generate_id(placeholder_id* placeholder)
    {
        id_data* data = placeholder->data;

        if (!data->generation_data)
        {
            std::string const& name = data->name;

            std::size_t seperator = name.rfind('.') + 1;
            data->generation_data.reset(new id_generation_data(
                std::string(name, 0, seperator),
                normalize_id(std::string(name, seperator))
            ));

            try_potential_id(placeholder);
        }

        while(!try_counted_id(placeholder)) {};
    }

    bool id_generator::try_potential_id(placeholder_id* placeholder)
    {
        placeholder->final_id =
            placeholder->data->generation_data->parent +
            placeholder->data->generation_data->base;

        // Be careful here as it's quite likely that final_id is the
        // same as the original id, so this will just find the original
        // data.
        //
        // Not caring too much about 'category' and 'used', would want to if
        // still creating ids.
        std::pair<boost::unordered_map<std::string, id_data>::iterator, bool>
            insert = ids.emplace(boost::unordered::piecewise_construct,
                boost::make_tuple(placeholder->final_id),
                boost::make_tuple(placeholder->final_id,
                    placeholder->category, true));
        
        if (insert.first->second.generation_data)
        {
            placeholder->data->generation_data =
                insert.first->second.generation_data;
        }
        else
        {
            insert.first->second.generation_data =
                placeholder->data->generation_data;
        }

        return insert.second;
    }

    bool id_generator::try_counted_id(placeholder_id* placeholder)
    {
        std::string name =
            placeholder->data->generation_data->base +
            (placeholder->data->generation_data->needs_underscore ? "_" : "") +
            boost::lexical_cast<std::string>(
                    placeholder->data->generation_data->count);

        if (name.length() > max_size)
        {
            std::size_t new_end =
                placeholder->data->generation_data->base.length() -
                    (name.length() - max_size);

            while (new_end > 0 &&
                std::isdigit(placeholder->data->generation_data->base[new_end - 1]))
                    --new_end;

            placeholder->data->generation_data->base.erase(new_end);
            placeholder->data->generation_data->new_base_value();

            // Return result of try_potential_id to use the truncated id
            // without a number.
            try_potential_id(placeholder);
            return false;
        }

        placeholder->final_id =
            placeholder->data->generation_data->parent + name;

        std::pair<boost::unordered_map<std::string, id_data>::iterator, bool>
            insert = ids.emplace(boost::unordered::piecewise_construct,
                boost::make_tuple(placeholder->final_id),
                boost::make_tuple(placeholder->final_id,
                    placeholder->category, true));

        ++placeholder->data->generation_data->count;

        return insert.second;
    }

    void id_generator::id_generation_data::new_base_value() {
        count = 0;
        needs_underscore = !base.empty() &&
            std::isdigit(base[base.length() - 1]);
    }

    // Very simple xml subset parser which replaces id values.
    //
    // I originally tried to integrate this into the post processor
    // but that proved tricky. Alternatively it could use a proper
    // xml parser, but I want this to be able to survive badly
    // marked up escapes.

    struct xml_processor
    {
        xml_processor();
    
        std::string escape_prefix;
        std::string escape_postfix;
        std::string processing_instruction_postfix;
        std::string comment_postfix;
        std::string whitespace;
        std::string tag_end;
        std::string name_end;
        std::string attribute_assign;
        std::vector<std::string> id_attributes;
        
        std::string replace(std::string const&, id_generator&);
    };

    std::string id_generator::replace_placeholders(std::string const& source)
    {
        xml_processor processor;
        return processor.replace(source, *this);
    }

    namespace
    {
        char const* id_attributes_[] =
        {
            "id",
            "linkend",
            "linkends",
            "arearefs"
        };
    }

    xml_processor::xml_processor()
        : escape_prefix("<!--quickbook-escape-prefix-->")
        , escape_postfix("<!--quickbook-escape-postfix-->")
        , processing_instruction_postfix("?>")
        , comment_postfix("-->")
        , whitespace(" \t\n\r")
        , tag_end(" \t\n\r>")
        , name_end("= \t\n\r>")
        , attribute_assign("= \t\n\r")
    {
        static int const n_id_attributes = sizeof(id_attributes_)/sizeof(char const*);
        for (int i = 0; i != n_id_attributes; ++i)
        {
            id_attributes.push_back(id_attributes_[i]);
        }

        std::sort(id_attributes.begin(), id_attributes.end());
    }

    std::string xml_processor::replace(std::string const& source, id_generator& ids)
    {
        std::string result;

        typedef std::string::const_iterator iterator;

        // copied is the point up to which the source has been copied, or
        // replaced, to result.
        iterator copied = source.begin();

        iterator end = source.end();

        for(iterator it = copied; it != end; it = std::find(it, end, '<'))
        {
            assert(copied <= it && it <= end);        

            if (static_cast<std::size_t>(end - it) > escape_prefix.size() &&
                    std::equal(escape_prefix.begin(), escape_prefix.end(), it))
            {
                it = std::search(it + escape_prefix.size(), end,
                    escape_postfix.begin(), escape_postfix.end());

                if (it == end) break;

                it += escape_postfix.size();
                continue;
            }

            ++it;
            if (it == end) break;

            switch(*it)
            {
            case '?':
                it = std::search(it, end,
                    processing_instruction_postfix.begin(),
                    processing_instruction_postfix.end());
                break;

            case '!':
                if (end - it > 3 && it[1] == '-' && it[2] == '-')
                {
                    it = std::search(it + 3, end,
                        comment_postfix. begin(), comment_postfix.end());
                    if (it != end) it += comment_postfix.size();
                }
                else
                {
                    it = std::find(it, end, '>');
                }
                break;

            default:
                if ((*it >= 'a' && *it <= 'z') ||
                        (*it >= 'A' && *it <= 'Z') ||
                        *it == '_' || *it == ':')
                {
                    it = std::find_first_of(
                        it + 1, end, tag_end.begin(), tag_end.end());

                    for (;;) {
                        while(it != end &&
                                std::find(whitespace.begin(),
                                    whitespace.end(), *it)
                                != whitespace.end())
                            ++it;
                            
                        iterator name_start = it;

                        it = std::find_first_of(
                            it, end, name_end.begin(), name_end.end());
                        
                        if (it == end || *it == '>') break;

                        string_ref name(name_start, it);
                        ++it;

                        while (it != end &&
                                std::find(attribute_assign.begin(),
                                    attribute_assign.end(), *it)
                                != attribute_assign.end())
                            ++it;

                        if (it == end || (*it != '"' && *it != '\'')) break;

                        char delim = *it;
                        ++it;

                        iterator value_start = it;

                        it = std::find(it, end, delim);
                        string_ref value(value_start, it);
                        if (it == end) break;
                        ++it;

                        if (std::find(id_attributes.begin(), id_attributes.end(),
                                    name)
                                != id_attributes.end())
                        {
                            result.append(copied, value.begin());
                            string_ref x = ids.get(value);
                            result.append(x.begin(), x.end());
                            copied = value.end();
                        }
                    }
                }
                else
                {
                    it = std::find(it, end, '>');
                }
            }
        }
        
        result.append(copied, source.end());
        return result;
    }
}
