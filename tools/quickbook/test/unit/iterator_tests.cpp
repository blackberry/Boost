/*=============================================================================
    Copyright (c) 2011 Daniel James

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

// Use boost's iterator concept tests for our iterators.

#include "fwd.hpp"
#include "values.hpp"
#include <boost/iterator/new_iterator_tests.hpp>
#include <boost/iterator/iterator_concepts.hpp>
#include <boost/concept_check.hpp>

void iterator_concept_checks()
{
    typedef quickbook::iterator Iter;
    boost::function_requires< boost::ForwardIterator<Iter> >();
    boost::function_requires< boost_concepts::ReadableIteratorConcept<Iter> >();
    boost::function_requires< boost_concepts::LvalueIteratorConcept<Iter> >();
    boost::function_requires< boost_concepts::ForwardTraversalConcept<Iter> >();
}

void value_iterator_concept_checks()
{
    typedef quickbook::value::iterator Iter;
    boost::function_requires< boost::ForwardIterator<Iter> >();
    boost::function_requires< boost_concepts::ReadableIteratorConcept<Iter> >();
    boost::function_requires< boost_concepts::ForwardTraversalConcept<Iter> >();
}

void iterator_runtime_checks()
{
    std::string x = "Hello World";

    quickbook::iterator i1(x.begin(), quickbook::file_position(10, 5));
    quickbook::iterator i2(++x.begin(), quickbook::file_position(10, 6));
    
    boost::forward_readable_iterator_test(i1, i2, 'H', 'e');
    boost::constant_lvalue_iterator_test(i1, 'H');
}

void value_iterator_runtime_checks()
{
    quickbook::value v1 = quickbook::bbk_value("a", 10);
    quickbook::value v2 = quickbook::int_value(25, 32);

    quickbook::value_builder b;
    b.insert(v1);
    b.insert(v2);
    quickbook::value x = b.release();    

    quickbook::value::iterator i1 = x.begin();
    quickbook::value::iterator i2 = ++x.begin();

    boost::forward_readable_iterator_test(i1, i2, v1, v2);
}

int main()
{
    // I know I don't have to run the concept checks.
    // I'm a bit irrational like that.
    iterator_concept_checks();
    value_iterator_concept_checks();
    iterator_runtime_checks();
    value_iterator_runtime_checks();

    return boost::report_errors();
}
