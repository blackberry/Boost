/*=============================================================================
    Copyright (c) 2002 2004 2006 Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_QUICKBOOK_UTILS_HPP)
#define BOOST_SPIRIT_QUICKBOOK_UTILS_HPP

#include <string>
#include <cctype>
#include <boost/assert.hpp>
#include <boost/filesystem/v3/path.hpp>
#include <boost/range/algorithm_ext/push_back.hpp>
#include <boost/range/adaptor/transformed.hpp>


namespace quickbook {

    namespace fs = boost::filesystem;

namespace detail
{
    void print_char(char ch, std::ostream& out);
    void print_string(std::basic_string<char> const& str, std::ostream& out);
    void print_space(char ch, std::ostream& out);
    char filter_identifier_char(char ch);

    template <typename Range>
    inline std::string
    make_identifier(Range const& range)
    {
        std::string out_name;

        boost::push_back(out_name,
            range | boost::adaptors::transformed(filter_identifier_char));

        return out_name;
    }

    // un-indent a code segment
    void unindent(std::string& program);

    std::string escape_uri(std::string uri);

    // load file into memory with extra trailing newlines to eliminate
    //  the need to check for end of file in the grammar.
    int load(fs::path const& filename, std::string& storage);

    // given a file extension, return the type of the source file
    // we'll have an internal database for known file types.

    enum file_type
    {
        cpp_file
      , python_file
    };

    file_type get_file_type(std::string const& extension);
}}

#endif // BOOST_SPIRIT_QUICKBOOK_UTILS_HPP

