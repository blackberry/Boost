/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// test_z.cpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#if 0
// test template
#include <cstddef>
#include <fstream>

#include <cstdio> // remove
#include <boost/config.hpp>
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{ 
    using ::remove;
}
#endif

#include <boost/archive/archive_exception.hpp>
#include "test_tools.hpp"

#include <boost/serialization/deque.hpp>

#include "A.hpp"
#include "A.ipp"

int test_main( int /* argc */, char* /* argv */[] )
{
    const char * testfile = boost::archive::tmpnam(NULL);
    BOOST_REQUIRE(NULL != testfile);

    // test array of objects
    std::deque<A> adeque, adeque1;
    {   
        test_ostream os(testfile, TEST_STREAM_FLAGS);
        test_oarchive oa(os, TEST_ARCHIVE_FLAGS);
        oa << boost::serialization::make_nvp("adeque",adeque);
    }
    {
        test_istream is(testfile, TEST_STREAM_FLAGS);
        test_iarchive ia(is, TEST_ARCHIVE_FLAGS);
        ia >> boost::serialization::make_nvp("adeque",adeque1);
    }
    BOOST_CHECK(adeque == adeque1);
    
    std::remove(testfile);
    return EXIT_SUCCESS;
}
#endif

//============================================================================
// Name        : boost_bug.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
//============================================================================

#include <iostream>
#include <fstream>
#include <iostream>
#include <iostream>
#include <boost/archive/text_oarchive.hpp>


class MyClassA
{
public:
	MyClassA(int x):xx(x){};
	int xx;
private:

	friend class boost::serialization::access;

	template<class Archive>
	void save(Archive & ar, const unsigned int version) const {
		//ar << xx;
	}

	template<class Archive>
	void load(Archive & ar, const unsigned int version) {
		//ar >> xx;
	}

	BOOST_SERIALIZATION_SPLIT_MEMBER();
};

int main() {
	 MyClassA clsA(12);
	std::ofstream f("/tmp/boost_clsA", std::ios::binary);
	if (f.fail()) return -1;
	boost::archive::text_oarchive oa(f);
	oa << clsA;
	f.close();
	return 0;
}
