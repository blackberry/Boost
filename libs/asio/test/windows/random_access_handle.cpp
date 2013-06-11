//
// random_access_handle.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~
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
#include <boost/asio/windows/random_access_handle.hpp>

#include <boost/asio/io_service.hpp>
#include "../unit_test.hpp"

//------------------------------------------------------------------------------

// windows_random_access_handle_compile test
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// The following test checks that all public member functions on the class
// windows::random_access_handle compile and link correctly. Runtime failures
// are ignored.

namespace windows_random_access_handle_compile {

void write_some_handler(const boost::system::error_code&, std::size_t)
{
}

void read_some_handler(const boost::system::error_code&, std::size_t)
{
}

void test()
{
#if defined(BOOST_ASIO_HAS_WINDOWS_RANDOM_ACCESS_HANDLE)
  using namespace boost::asio;
  namespace win = boost::asio::windows;

  try
  {
    io_service ios;
    char mutable_char_buffer[128] = "";
    const char const_char_buffer[128] = "";
    boost::uint64_t offset = 0;
    boost::system::error_code ec;

    // basic_random_access_handle constructors.

    win::random_access_handle handle1(ios);
    HANDLE native_handle1 = INVALID_HANDLE_VALUE;
    win::random_access_handle handle2(ios, native_handle1);

#if defined(BOOST_ASIO_HAS_MOVE)
    win::random_access_handle handle3(std::move(handle2));
#endif // defined(BOOST_ASIO_HAS_MOVE)

    // basic_random_access_handle operators.

#if defined(BOOST_ASIO_HAS_MOVE)
    handle1 = win::random_access_handle(ios);
    handle1 = std::move(handle2);
#endif // defined(BOOST_ASIO_HAS_MOVE)

    // basic_io_object functions.

    io_service& ios_ref = handle1.get_io_service();
    (void)ios_ref;

    // basic_handle functions.

    win::random_access_handle::lowest_layer_type& lowest_layer
      = handle1.lowest_layer();
    (void)lowest_layer;

    const win::random_access_handle& handle4 = handle1;
    const win::random_access_handle::lowest_layer_type& lowest_layer2
      = handle4.lowest_layer();
    (void)lowest_layer2;

    HANDLE native_handle2 = INVALID_HANDLE_VALUE;
    handle1.assign(native_handle2);

    bool is_open = handle1.is_open();
    (void)is_open;

    handle1.close();
    handle1.close(ec);

    win::random_access_handle::native_type native_handle3 = handle1.native();
    (void)native_handle3;

    win::random_access_handle::native_handle_type native_handle4
      = handle1.native_handle();
    (void)native_handle4;

    handle1.cancel();
    handle1.cancel(ec);

    // basic_random_access_handle functions.

    handle1.write_some_at(offset, buffer(mutable_char_buffer));
    handle1.write_some_at(offset, buffer(const_char_buffer));
    handle1.write_some_at(offset, buffer(mutable_char_buffer), ec);
    handle1.write_some_at(offset, buffer(const_char_buffer), ec);

    handle1.async_write_some_at(offset,
        buffer(mutable_char_buffer), &write_some_handler);
    handle1.async_write_some_at(offset,
        buffer(const_char_buffer), &write_some_handler);

    handle1.read_some_at(offset, buffer(mutable_char_buffer));
    handle1.read_some_at(offset, buffer(mutable_char_buffer), ec);

    handle1.async_read_some_at(offset,
        buffer(mutable_char_buffer), &read_some_handler);
  }
  catch (std::exception&)
  {
  }
#endif // defined(BOOST_ASIO_HAS_WINDOWS_RANDOM_ACCESS_HANDLE)
}

} // namespace windows_random_access_handle_compile

//------------------------------------------------------------------------------
test_suite* init_unit_test_suite(int, char*[])
{
  test_suite* test = BOOST_TEST_SUITE("windows/random_access_handle");
  test->add(BOOST_TEST_CASE(&windows_random_access_handle_compile::test));
  return test;
}
