//  Unit test for boost::lexical_cast.
//
//  See http://www.boost.org for most recent version, including documentation.
//
//  Copyright Antony Polukhin, 2011.
//
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt).

#include <boost/config.hpp>

#if defined(__INTEL_COMPILER)
#pragma warning(disable: 193 383 488 981 1418 1419)
#elif defined(BOOST_MSVC)
#pragma warning(disable: 4097 4100 4121 4127 4146 4244 4245 4511 4512 4701 4800)
#endif

#include <boost/lexical_cast.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/range/iterator_range.hpp>

using namespace boost;

void test_empty_iterator_range()
{
		boost::iterator_range<const char*> v;
    BOOST_CHECK_THROW(lexical_cast<int>(v), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<float>(v), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<double>(v), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<long double>(v), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<unsigned int>(v), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<std::string>(v), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<unsigned short>(v), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<char>(v), bad_lexical_cast);
}

void test_empty_string()
{
    BOOST_CHECK_THROW(lexical_cast<int>(std::string()), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<float>(std::string()), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<double>(std::string()), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<long double>(std::string()), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<unsigned int>(std::string()), bad_lexical_cast);
    BOOST_CHECK_EQUAL(lexical_cast<std::string>(std::string()), std::string());
    BOOST_CHECK_THROW(lexical_cast<unsigned short>(std::string()), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<char>(std::string()), bad_lexical_cast);
}

unit_test::test_suite *init_unit_test_suite(int, char *[])
{
    unit_test_framework::test_suite *suite =
        BOOST_TEST_SUITE("lexical_cast. Empty input unit test");
    suite->add(BOOST_TEST_CASE(&test_empty_iterator_range));
    suite->add(BOOST_TEST_CASE(&test_empty_string));

    return suite;
}
