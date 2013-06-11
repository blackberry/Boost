//
// buffered_stream.cpp
// ~~~~~~~~~~~~~~~~~~~
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
#include <boost/asio/buffered_stream.hpp>

#include <boost/bind.hpp>
#include <cstring>
#include <boost/asio/buffer.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/system/system_error.hpp>
#include "unit_test.hpp"

typedef boost::asio::buffered_stream<
    boost::asio::ip::tcp::socket> stream_type;

void test_sync_operations()
{
  using namespace std; // For memcmp.

  boost::asio::io_service io_service;

  boost::asio::ip::tcp::acceptor acceptor(io_service,
      boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 0));
  boost::asio::ip::tcp::endpoint server_endpoint = acceptor.local_endpoint();
  server_endpoint.address(boost::asio::ip::address_v4::loopback());

  stream_type client_socket(io_service);
  client_socket.lowest_layer().connect(server_endpoint);

  stream_type server_socket(io_service);
  acceptor.accept(server_socket.lowest_layer());

  const char write_data[]
    = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  const boost::asio::const_buffer write_buf = boost::asio::buffer(write_data);

  std::size_t bytes_written = 0;
  while (bytes_written < sizeof(write_data))
  {
    bytes_written += client_socket.write_some(
        boost::asio::buffer(write_buf + bytes_written));
    client_socket.flush();
  }

  char read_data[sizeof(write_data)];
  const boost::asio::mutable_buffer read_buf = boost::asio::buffer(read_data);

  std::size_t bytes_read = 0;
  while (bytes_read < sizeof(read_data))
  {
    bytes_read += server_socket.read_some(
        boost::asio::buffer(read_buf + bytes_read));
  }

  BOOST_CHECK(bytes_written == sizeof(write_data));
  BOOST_CHECK(bytes_read == sizeof(read_data));
  BOOST_CHECK(memcmp(write_data, read_data, sizeof(write_data)) == 0);

  bytes_written = 0;
  while (bytes_written < sizeof(write_data))
  {
    bytes_written += server_socket.write_some(
        boost::asio::buffer(write_buf + bytes_written));
    server_socket.flush();
  }

  bytes_read = 0;
  while (bytes_read < sizeof(read_data))
  {
    bytes_read += client_socket.read_some(
        boost::asio::buffer(read_buf + bytes_read));
  }

  BOOST_CHECK(bytes_written == sizeof(write_data));
  BOOST_CHECK(bytes_read == sizeof(read_data));
  BOOST_CHECK(memcmp(write_data, read_data, sizeof(write_data)) == 0);

  server_socket.close();
  boost::system::error_code error;
  bytes_read = client_socket.read_some(
      boost::asio::buffer(read_buf), error);

  BOOST_CHECK(bytes_read == 0);
  BOOST_CHECK(error == boost::asio::error::eof);

  client_socket.close(error);
}

void handle_accept(const boost::system::error_code& e)
{
  BOOST_CHECK(!e);
}

void handle_write(const boost::system::error_code& e,
    std::size_t bytes_transferred,
    std::size_t* total_bytes_written)
{
  BOOST_CHECK(!e);
  if (e)
    throw boost::system::system_error(e); // Terminate test.
  *total_bytes_written += bytes_transferred;
}

void handle_flush(const boost::system::error_code& e)
{
  BOOST_CHECK(!e);
}

void handle_read(const boost::system::error_code& e,
    std::size_t bytes_transferred,
    std::size_t* total_bytes_read)
{
  BOOST_CHECK(!e);
  if (e)
    throw boost::system::system_error(e); // Terminate test.
  *total_bytes_read += bytes_transferred;
}

void handle_read_eof(const boost::system::error_code& e,
    std::size_t bytes_transferred)
{
  BOOST_CHECK(e == boost::asio::error::eof);
  BOOST_CHECK(bytes_transferred == 0);
}

void test_async_operations()
{
  using namespace std; // For memcmp.

  boost::asio::io_service io_service;

  boost::asio::ip::tcp::acceptor acceptor(io_service,
      boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 0));
  boost::asio::ip::tcp::endpoint server_endpoint = acceptor.local_endpoint();
  server_endpoint.address(boost::asio::ip::address_v4::loopback());

  stream_type client_socket(io_service);
  client_socket.lowest_layer().connect(server_endpoint);

  stream_type server_socket(io_service);
  acceptor.async_accept(server_socket.lowest_layer(), &handle_accept);
  io_service.run();
  io_service.reset();

  const char write_data[]
    = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  const boost::asio::const_buffer write_buf = boost::asio::buffer(write_data);

  std::size_t bytes_written = 0;
  while (bytes_written < sizeof(write_data))
  {
    client_socket.async_write_some(
        boost::asio::buffer(write_buf + bytes_written),
        boost::bind(handle_write, boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred, &bytes_written));
    io_service.run();
    io_service.reset();
    client_socket.async_flush(
        boost::bind(handle_flush, boost::asio::placeholders::error));
    io_service.run();
    io_service.reset();
  }

  char read_data[sizeof(write_data)];
  const boost::asio::mutable_buffer read_buf = boost::asio::buffer(read_data);

  std::size_t bytes_read = 0;
  while (bytes_read < sizeof(read_data))
  {
    server_socket.async_read_some(
        boost::asio::buffer(read_buf + bytes_read),
        boost::bind(handle_read, boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred, &bytes_read));
    io_service.run();
    io_service.reset();
  }

  BOOST_CHECK(bytes_written == sizeof(write_data));
  BOOST_CHECK(bytes_read == sizeof(read_data));
  BOOST_CHECK(memcmp(write_data, read_data, sizeof(write_data)) == 0);

  bytes_written = 0;
  while (bytes_written < sizeof(write_data))
  {
    server_socket.async_write_some(
        boost::asio::buffer(write_buf + bytes_written),
        boost::bind(handle_write, boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred, &bytes_written));
    io_service.run();
    io_service.reset();
    server_socket.async_flush(
        boost::bind(handle_flush, boost::asio::placeholders::error));
    io_service.run();
    io_service.reset();
  }

  bytes_read = 0;
  while (bytes_read < sizeof(read_data))
  {
    client_socket.async_read_some(
        boost::asio::buffer(read_buf + bytes_read),
        boost::bind(handle_read, boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred, &bytes_read));
    io_service.run();
    io_service.reset();
  }

  BOOST_CHECK(bytes_written == sizeof(write_data));
  BOOST_CHECK(bytes_read == sizeof(read_data));
  BOOST_CHECK(memcmp(write_data, read_data, sizeof(write_data)) == 0);

  server_socket.close();
  client_socket.async_read_some(boost::asio::buffer(read_buf), handle_read_eof);
}

test_suite* init_unit_test_suite(int, char*[])
{
  test_suite* test = BOOST_TEST_SUITE("buffered_stream");
  test->add(BOOST_TEST_CASE(&test_sync_operations));
  test->add(BOOST_TEST_CASE(&test_async_operations));
  return test;
}
