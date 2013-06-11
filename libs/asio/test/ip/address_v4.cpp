//
// address_v4.cpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2012 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Disable autolinking for unit tests.
#if !defined(BOOST_ALL_NO_LIB)
#define BOOST_ALL_NO_LIB 1
#endif // !defined(BOOST_ALL_NO_LIB)

// Test that header file is self-contained.
#include <boost/asio/ip/address_v4.hpp>

#include "../unit_test.hpp"
#include <sstream>

//------------------------------------------------------------------------------

// ip_address_v4_compile test
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
// The following test checks that all public member functions on the class
// ip::address_v4 compile and link correctly. Runtime failures are ignored.

namespace ip_address_v4_compile {

void test()
{
  using namespace boost::asio;
  namespace ip = boost::asio::ip;

  try
  {
    boost::system::error_code ec;

    // address_v4 constructors.

    ip::address_v4 addr1;
    const ip::address_v4::bytes_type const_bytes_value = { { 127, 0, 0, 1 } };
    ip::address_v4 addr2(const_bytes_value);
    const unsigned long const_ulong_value = 0x7F000001;
    ip::address_v4 addr3(const_ulong_value);

    // address_v4 functions.

    bool b = addr1.is_loopback();
    (void)b;

    b = addr1.is_unspecified();
    (void)b;

    b = addr1.is_class_a();
    (void)b;

    b = addr1.is_class_b();
    (void)b;

    b = addr1.is_class_c();
    (void)b;

    b = addr1.is_multicast();
    (void)b;

    ip::address_v4::bytes_type bytes_value = addr1.to_bytes();
    (void)bytes_value;

    unsigned long ulong_value = addr1.to_ulong();
    (void)ulong_value;

    std::string string_value = addr1.to_string();
    string_value = addr1.to_string(ec);

    // address_v4 static functions.

    addr1 = ip::address_v4::from_string("127.0.0.1");
    addr1 = ip::address_v4::from_string("127.0.0.1", ec);
    addr1 = ip::address_v4::from_string(string_value);
    addr1 = ip::address_v4::from_string(string_value, ec);

    addr1 = ip::address_v4::any();

    addr1 = ip::address_v4::loopback();

    addr1 = ip::address_v4::broadcast();

    addr1 = ip::address_v4::broadcast(addr2, addr3);

    addr1 = ip::address_v4::netmask(addr2);

    // address_v4 comparisons.

    b = (addr1 == addr2);
    (void)b;

    b = (addr1 != addr2);
    (void)b;

    b = (addr1 < addr2);
    (void)b;

    b = (addr1 > addr2);
    (void)b;

    b = (addr1 <= addr2);
    (void)b;

    b = (addr1 >= addr2);
    (void)b;

    // address_v4 I/O.

    std::ostringstream os;
    os << addr1;

#if !defined(BOOST_NO_STD_WSTREAMBUF)
    std::wostringstream wos;
    wos << addr1;
#endif // !defined(BOOST_NO_STD_WSTREAMBUF)
  }
  catch (std::exception&)
  {
  }
}

} // namespace ip_address_v4_compile

//------------------------------------------------------------------------------

// ip_address_v4_runtime test
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
// The following test checks that the various public member functions meet the
// necessary postconditions.

namespace ip_address_v4_runtime {

void test()
{
  using boost::asio::ip::address_v4;

  address_v4 a1;
  BOOST_CHECK(a1.to_bytes()[0] == 0);
  BOOST_CHECK(a1.to_bytes()[1] == 0);
  BOOST_CHECK(a1.to_bytes()[2] == 0);
  BOOST_CHECK(a1.to_bytes()[3] == 0);
  BOOST_CHECK(a1.to_ulong() == 0);

  address_v4::bytes_type b1 = {{ 1, 2, 3, 4 }};
  address_v4 a2(b1);
  BOOST_CHECK(a2.to_bytes()[0] == 1);
  BOOST_CHECK(a2.to_bytes()[1] == 2);
  BOOST_CHECK(a2.to_bytes()[2] == 3);
  BOOST_CHECK(a2.to_bytes()[3] == 4);
  BOOST_CHECK(((a2.to_ulong() >> 24) & 0xFF) == b1[0]);
  BOOST_CHECK(((a2.to_ulong() >> 16) & 0xFF) == b1[1]);
  BOOST_CHECK(((a2.to_ulong() >> 8) & 0xFF) == b1[2]);
  BOOST_CHECK((a2.to_ulong() & 0xFF) == b1[3]);

  address_v4 a3(0x01020304);
  BOOST_CHECK(a3.to_bytes()[0] == 1);
  BOOST_CHECK(a3.to_bytes()[1] == 2);
  BOOST_CHECK(a3.to_bytes()[2] == 3);
  BOOST_CHECK(a3.to_bytes()[3] == 4);
  BOOST_CHECK(a3.to_ulong() == 0x01020304);

  BOOST_CHECK(address_v4(0x7F000001).is_loopback());
  BOOST_CHECK(address_v4(0x7F000002).is_loopback());
  BOOST_CHECK(!address_v4(0x00000000).is_loopback());
  BOOST_CHECK(!address_v4(0x01020304).is_loopback());

  BOOST_CHECK(address_v4(0x00000000).is_unspecified());
  BOOST_CHECK(!address_v4(0x7F000001).is_unspecified());
  BOOST_CHECK(!address_v4(0x01020304).is_unspecified());

  BOOST_CHECK(address_v4(0x01000000).is_class_a());
  BOOST_CHECK(address_v4(0x7F000000).is_class_a());
  BOOST_CHECK(!address_v4(0x80000000).is_class_a());
  BOOST_CHECK(!address_v4(0xBFFF0000).is_class_a());
  BOOST_CHECK(!address_v4(0xC0000000).is_class_a());
  BOOST_CHECK(!address_v4(0xDFFFFF00).is_class_a());
  BOOST_CHECK(!address_v4(0xE0000000).is_class_a());
  BOOST_CHECK(!address_v4(0xEFFFFFFF).is_class_a());
  BOOST_CHECK(!address_v4(0xF0000000).is_class_a());
  BOOST_CHECK(!address_v4(0xFFFFFFFF).is_class_a());

  BOOST_CHECK(!address_v4(0x01000000).is_class_b());
  BOOST_CHECK(!address_v4(0x7F000000).is_class_b());
  BOOST_CHECK(address_v4(0x80000000).is_class_b());
  BOOST_CHECK(address_v4(0xBFFF0000).is_class_b());
  BOOST_CHECK(!address_v4(0xC0000000).is_class_b());
  BOOST_CHECK(!address_v4(0xDFFFFF00).is_class_b());
  BOOST_CHECK(!address_v4(0xE0000000).is_class_b());
  BOOST_CHECK(!address_v4(0xEFFFFFFF).is_class_b());
  BOOST_CHECK(!address_v4(0xF0000000).is_class_b());
  BOOST_CHECK(!address_v4(0xFFFFFFFF).is_class_b());

  BOOST_CHECK(!address_v4(0x01000000).is_class_c());
  BOOST_CHECK(!address_v4(0x7F000000).is_class_c());
  BOOST_CHECK(!address_v4(0x80000000).is_class_c());
  BOOST_CHECK(!address_v4(0xBFFF0000).is_class_c());
  BOOST_CHECK(address_v4(0xC0000000).is_class_c());
  BOOST_CHECK(address_v4(0xDFFFFF00).is_class_c());
  BOOST_CHECK(!address_v4(0xE0000000).is_class_c());
  BOOST_CHECK(!address_v4(0xEFFFFFFF).is_class_c());
  BOOST_CHECK(!address_v4(0xF0000000).is_class_c());
  BOOST_CHECK(!address_v4(0xFFFFFFFF).is_class_c());

  BOOST_CHECK(!address_v4(0x01000000).is_multicast());
  BOOST_CHECK(!address_v4(0x7F000000).is_multicast());
  BOOST_CHECK(!address_v4(0x80000000).is_multicast());
  BOOST_CHECK(!address_v4(0xBFFF0000).is_multicast());
  BOOST_CHECK(!address_v4(0xC0000000).is_multicast());
  BOOST_CHECK(!address_v4(0xDFFFFF00).is_multicast());
  BOOST_CHECK(address_v4(0xE0000000).is_multicast());
  BOOST_CHECK(address_v4(0xEFFFFFFF).is_multicast());
  BOOST_CHECK(!address_v4(0xF0000000).is_multicast());
  BOOST_CHECK(!address_v4(0xFFFFFFFF).is_multicast());

  address_v4 a4 = address_v4::any();
  BOOST_CHECK(a4.to_bytes()[0] == 0);
  BOOST_CHECK(a4.to_bytes()[1] == 0);
  BOOST_CHECK(a4.to_bytes()[2] == 0);
  BOOST_CHECK(a4.to_bytes()[3] == 0);
  BOOST_CHECK(a4.to_ulong() == 0);

  address_v4 a5 = address_v4::loopback();
  BOOST_CHECK(a5.to_bytes()[0] == 0x7F);
  BOOST_CHECK(a5.to_bytes()[1] == 0);
  BOOST_CHECK(a5.to_bytes()[2] == 0);
  BOOST_CHECK(a5.to_bytes()[3] == 0x01);
  BOOST_CHECK(a5.to_ulong() == 0x7F000001);

  address_v4 a6 = address_v4::broadcast();
  BOOST_CHECK(a6.to_bytes()[0] == 0xFF);
  BOOST_CHECK(a6.to_bytes()[1] == 0xFF);
  BOOST_CHECK(a6.to_bytes()[2] == 0xFF);
  BOOST_CHECK(a6.to_bytes()[3] == 0xFF);
  BOOST_CHECK(a6.to_ulong() == 0xFFFFFFFF);

  address_v4 class_a_net(0xFF000000);
  address_v4 class_b_net(0xFFFF0000);
  address_v4 class_c_net(0xFFFFFF00);
  address_v4 other_net(0xFFFFFFFF);
  BOOST_CHECK(address_v4::netmask(address_v4(0x01000000)) == class_a_net);
  BOOST_CHECK(address_v4::netmask(address_v4(0x7F000000)) == class_a_net);
  BOOST_CHECK(address_v4::netmask(address_v4(0x80000000)) == class_b_net);
  BOOST_CHECK(address_v4::netmask(address_v4(0xBFFF0000)) == class_b_net);
  BOOST_CHECK(address_v4::netmask(address_v4(0xC0000000)) == class_c_net);
  BOOST_CHECK(address_v4::netmask(address_v4(0xDFFFFF00)) == class_c_net);
  BOOST_CHECK(address_v4::netmask(address_v4(0xE0000000)) == other_net);
  BOOST_CHECK(address_v4::netmask(address_v4(0xEFFFFFFF)) == other_net);
  BOOST_CHECK(address_v4::netmask(address_v4(0xF0000000)) == other_net);
  BOOST_CHECK(address_v4::netmask(address_v4(0xFFFFFFFF)) == other_net);
}

} // namespace ip_address_v4_runtime

//------------------------------------------------------------------------------

test_suite* init_unit_test_suite(int, char*[])
{
  test_suite* test = BOOST_TEST_SUITE("ip/address_v4");
  test->add(BOOST_TEST_CASE(&ip_address_v4_compile::test));
  test->add(BOOST_TEST_CASE(&ip_address_v4_runtime::test));
  return test;
}
