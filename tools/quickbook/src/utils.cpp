/*=============================================================================
    Copyright (c) 2002 2004 2006 Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#include "utils.hpp"
#include "input_path.hpp"
#include <boost/spirit/include/classic_core.hpp>
#include <boost/filesystem/v3/fstream.hpp>

#include <cctype>
#include <cstring>
#include <stdexcept>
#include <fstream>
#include <ostream>
#include <map>

namespace quickbook { namespace detail
{
    void print_char(char ch, std::ostream& out)
    {
        switch (ch)
        {
            case '<': out << "&lt;";    break;
            case '>': out << "&gt;";    break;
            case '&': out << "&amp;";   break;
            case '"': out << "&quot;";  break;
            default:  out << ch;        break;
            // note &apos; is not included. see the curse of apos:
            // http://fishbowl.pastiche.org/2003/07/01/the_curse_of_apos
        }
    }

    void print_string(std::basic_string<char> const& str, std::ostream& out)
    {
        for (std::string::const_iterator cur = str.begin();
            cur != str.end(); ++cur)
        {
            print_char(*cur, out);
        }
    }

    void print_space(char ch, std::ostream& out)
    {
        out << ch;
    }

    char filter_identifier_char(char ch)
    {
        if (!std::isalnum(static_cast<unsigned char>(ch)))
            ch = '_';
        return static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
    }

    // un-indent a code segment
    void unindent(std::string& program)
    {
        // Erase leading blank lines and newlines:
        std::string::size_type start = program.find_first_not_of(" \t");
        if (start != std::string::npos &&
            (program[start] == '\r' || program[start] == '\n'))
        {
            program.erase(0, start);
        }
        start = program.find_first_not_of("\r\n");
        program.erase(0, start);

        if (program.size() == 0)
            return; // nothing left to do

        // Get the first line indent
        std::string::size_type indent = program.find_first_not_of(" \t");
        std::string::size_type pos = 0;
        if (std::string::npos == indent)
        {
            // Nothing left to do here. The code is empty (just spaces).
            // We clear the program to signal the caller that it is empty
            // and return early.
            program.clear();
            return;
        }

        // Calculate the minimum indent from the rest of the lines
        do
        {
            pos = program.find_first_not_of("\r\n", pos);
            if (std::string::npos == pos)
                break;

            std::string::size_type n = program.find_first_not_of(" \t", pos);
            if (n != std::string::npos)
            {
                char ch = program[n];
                if (ch != '\r' && ch != '\n') // ignore empty lines
                    indent = (std::min)(indent, n-pos);
            }
        }
        while (std::string::npos != (pos = program.find_first_of("\r\n", pos)));

        // Trim white spaces from column 0..indent
        pos = 0;
        program.erase(0, indent);
        while (std::string::npos != (pos = program.find_first_of("\r\n", pos)))
        {
            if (std::string::npos == (pos = program.find_first_not_of("\r\n", pos)))
            {
                break;
            }

            std::string::size_type next = program.find_first_of("\r\n", pos);
            program.erase(pos, (std::min)(indent, next-pos));
        }
    }

    std::string escape_uri(std::string uri)
    {
        for (std::string::size_type n = 0; n < uri.size(); ++n)
        {
            static char const mark[] = "-_.!~*'()?\\/";
            if((!std::isalnum(static_cast<unsigned char>(uri[n])) || 127 < static_cast<unsigned char>(uri[n]))
              && 0 == std::strchr(mark, uri[n]))
            {
                static char const hex[] = "0123456789abcdef";
                char escape[] = { hex[uri[n] / 16], hex[uri[n] % 16] };
                uri.insert(n + 1, escape, 2);
                uri[n] = '%';
                n += 2;
            }
        }
        return uri;
    }

    // Read the first few bytes in a file to see it starts with a byte order
    // mark. If it doesn't, then write the characters we've already read in.
    // Although, given how UTF-8 works, if we've read anything in, the files
    // probably broken.

    template <typename InputIterator, typename OutputIterator>
    bool check_bom(InputIterator& begin, InputIterator end,
            OutputIterator out, char const* chars, int length)
    {
        char const* ptr = chars;

        while(begin != end && *begin == *ptr) {
            ++begin;
            ++ptr;
            --length;
            if(length == 0) return true;
        }

        // Failed to match, so write the skipped characters to storage:
        while(chars != ptr) *out++ = *chars++;

        return false;
    }
    
    template <typename InputIterator, typename OutputIterator>
    std::string read_bom(InputIterator& begin, InputIterator end,
            OutputIterator out)
    {
        if(begin == end) return "";

        const char* utf8 = "\xef\xbb\xbf" ;
        const char* utf32be = "\0\0\xfe\xff";
        const char* utf32le = "\xff\xfe\0\0";

        unsigned char c = *begin;
        switch(c)
        {
        case 0xEF: { // UTF-8
            return check_bom(begin, end, out, utf8, 3) ? "UTF-8" : "";
        }
        case 0xFF: // UTF-16/UTF-32 little endian
            return !check_bom(begin, end, out, utf32le, 2) ? "" :
                check_bom(begin, end, out, utf32le + 2, 2) ? "UTF-32" : "UTF-16";
        case 0: // UTF-32 big endian
            return check_bom(begin, end, out, utf32be, 4) ? "UTF-32" : "";
        case 0xFE: // UTF-16 big endian
            return check_bom(begin, end, out, utf32be + 2, 2) ? "UTF-16" : "";
        default:
            return "";
        }
    }

    // Copy a string, converting mac and windows style newlines to unix
    // newlines.

    template <typename InputIterator, typename OutputIterator>
    bool normalize(InputIterator begin, InputIterator end,
            OutputIterator out, fs::path const& filename)
    {
        std::string encoding = read_bom(begin, end, out);

        if(encoding != "UTF-8" && encoding != "") {
            outerr(filename) << encoding.c_str()
                << " is not supported. Please use UTF-8."
                << std::endl;

            return false;
        }
    
        while(begin != end) {
            if(*begin == '\r') {
                *out++ = '\n';
                ++begin;
                if(begin != end && *begin == '\n') ++begin;
            }
            else {
                *out++ = *begin++;
            }
        }
        
        return true;
    }

    int load(fs::path const& filename, std::string& storage)
    {
        using std::endl;
        using std::ios;
        using std::ifstream;
        using std::istream_iterator;

        fs::ifstream in(filename, std::ios_base::in);

        if (!in)
        {
            outerr(filename) << "Could not open input file." << endl;
            return 1;
        }

        // Turn off white space skipping on the stream
        in.unsetf(ios::skipws);

        if(!normalize(
            istream_iterator<char>(in),
            istream_iterator<char>(),
            std::back_inserter(storage),
            filename))
        {
            return 1;
        }

        //  ensure that we have enough trailing newlines to eliminate
        //  the need to check for end of file in the grammar.
        storage.push_back('\n');
        storage.push_back('\n');
        return 0;
    }

    file_type get_file_type(std::string const& extension)
    {
        static std::map<std::string, file_type> ftypes;
        if (ftypes.empty())
        {
            // init the map of types
            ftypes["cpp"] = cpp_file;
            ftypes["hpp"] = cpp_file;
            ftypes["h"] = cpp_file;
            ftypes["c"] = cpp_file;
            ftypes["cxx"] = cpp_file;
            ftypes["hxx"] = cpp_file;
            ftypes["ipp"] = cpp_file;
            ftypes["py"] = python_file;
        }
        return ftypes[extension];
    }

}}


