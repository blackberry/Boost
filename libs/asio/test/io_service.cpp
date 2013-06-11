//
// io_service.cpp
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
#include <boost/asio/io_service.hpp>

#include <sstream>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <boost/asio/deadline_timer.hpp>
#include "unit_test.hpp"

using namespace boost::asio;

void increment(int* count)
{
  ++(*count);
}

void decrement_to_zero(io_service* ios, int* count)
{
  if (*count > 0)
  {
    --(*count);

    int before_value = *count;
    ios->post(boost::bind(decrement_to_zero, ios, count));

    // Handler execution cannot nest, so count value should remain unchanged.
    BOOST_CHECK(*count == before_value);
  }
}

void nested_decrement_to_zero(io_service* ios, int* count)
{
  if (*count > 0)
  {
    --(*count);

    ios->dispatch(boost::bind(nested_decrement_to_zero, ios, count));

    // Handler execution is nested, so count value should now be zero.
    BOOST_CHECK(*count == 0);
  }
}

void sleep_increment(io_service* ios, int* count)
{
  deadline_timer t(*ios, boost::posix_time::seconds(2));
  t.wait();

  if (++(*count) < 3)
    ios->post(boost::bind(sleep_increment, ios, count));
}

void start_sleep_increments(io_service* ios, int* count)
{
  // Give all threads a chance to start.
  deadline_timer t(*ios, boost::posix_time::seconds(2));
  t.wait();

  // Start the first of three increments.
  ios->post(boost::bind(sleep_increment, ios, count));
}

void throw_exception()
{
  throw 1;
}

void io_service_run(io_service* ios)
{
  ios->run();
}

void io_service_test()
{
  io_service ios;
  int count = 0;

  ios.post(boost::bind(increment, &count));

  // No handlers can be called until run() is called.
  BOOST_CHECK(!ios.stopped());
  BOOST_CHECK(count == 0);

  ios.run();

  // The run() call will not return until all work has finished.
  BOOST_CHECK(ios.stopped());
  BOOST_CHECK(count == 1);

  count = 0;
  ios.reset();
  ios.post(boost::bind(increment, &count));
  ios.post(boost::bind(increment, &count));
  ios.post(boost::bind(increment, &count));
  ios.post(boost::bind(increment, &count));
  ios.post(boost::bind(increment, &count));

  // No handlers can be called until run() is called.
  BOOST_CHECK(!ios.stopped());
  BOOST_CHECK(count == 0);

  ios.run();

  // The run() call will not return until all work has finished.
  BOOST_CHECK(ios.stopped());
  BOOST_CHECK(count == 5);

  count = 0;
  ios.reset();
  io_service::work* w = new io_service::work(ios);
  ios.post(boost::bind(&io_service::stop, &ios));
  BOOST_CHECK(!ios.stopped());
  ios.run();

  // The only operation executed should have been to stop run().
  BOOST_CHECK(ios.stopped());
  BOOST_CHECK(count == 0);

  ios.reset();
  ios.post(boost::bind(increment, &count));
  delete w;

  // No handlers can be called until run() is called.
  BOOST_CHECK(!ios.stopped());
  BOOST_CHECK(count == 0);

  ios.run();

  // The run() call will not return until all work has finished.
  BOOST_CHECK(ios.stopped());
  BOOST_CHECK(count == 1);

  count = 10;
  ios.reset();
  ios.post(boost::bind(decrement_to_zero, &ios, &count));

  // No handlers can be called until run() is called.
  BOOST_CHECK(!ios.stopped());
  BOOST_CHECK(count == 10);

  ios.run();

  // The run() call will not return until all work has finished.
  BOOST_CHECK(ios.stopped());
  BOOST_CHECK(count == 0);

  count = 10;
  ios.reset();
  ios.post(boost::bind(nested_decrement_to_zero, &ios, &count));

  // No handlers can be called until run() is called.
  BOOST_CHECK(!ios.stopped());
  BOOST_CHECK(count == 10);

  ios.run();

  // The run() call will not return until all work has finished.
  BOOST_CHECK(ios.stopped());
  BOOST_CHECK(count == 0);

  count = 10;
  ios.reset();
  ios.dispatch(boost::bind(nested_decrement_to_zero, &ios, &count));

  // No handlers can be called until run() is called, even though nested
  // delivery was specifically allowed in the previous call.
  BOOST_CHECK(!ios.stopped());
  BOOST_CHECK(count == 10);

  ios.run();

  // The run() call will not return until all work has finished.
  BOOST_CHECK(ios.stopped());
  BOOST_CHECK(count == 0);

  count = 0;
  int count2 = 0;
  ios.reset();
  BOOST_CHECK(!ios.stopped());
  ios.post(boost::bind(start_sleep_increments, &ios, &count));
  ios.post(boost::bind(start_sleep_increments, &ios, &count2));
  boost::thread thread1(boost::bind(io_service_run, &ios));
  boost::thread thread2(boost::bind(io_service_run, &ios));
  thread1.join();
  thread2.join();

  // The run() calls will not return until all work has finished.
  BOOST_CHECK(ios.stopped());
  BOOST_CHECK(count == 3);
  BOOST_CHECK(count2 == 3);

  count = 10;
  io_service ios2;
  ios.dispatch(ios2.wrap(boost::bind(decrement_to_zero, &ios2, &count)));
  ios.reset();
  BOOST_CHECK(!ios.stopped());
  ios.run();

  // No decrement_to_zero handlers can be called until run() is called on the
  // second io_service object.
  BOOST_CHECK(ios.stopped());
  BOOST_CHECK(count == 10);

  ios2.run();

  // The run() call will not return until all work has finished.
  BOOST_CHECK(count == 0);

  count = 0;
  int exception_count = 0;
  ios.reset();
  ios.post(&throw_exception);
  ios.post(boost::bind(increment, &count));
  ios.post(boost::bind(increment, &count));
  ios.post(&throw_exception);
  ios.post(boost::bind(increment, &count));

  // No handlers can be called until run() is called.
  BOOST_CHECK(!ios.stopped());
  BOOST_CHECK(count == 0);
  BOOST_CHECK(exception_count == 0);

  for (;;)
  {
    try
    {
      ios.run();
      break;
    }
    catch (int)
    {
      ++exception_count;
    }
  }

  // The run() calls will not return until all work has finished.
  BOOST_CHECK(ios.stopped());
  BOOST_CHECK(count == 3);
  BOOST_CHECK(exception_count == 2);
}

class test_service : public boost::asio::io_service::service
{
public:
  static boost::asio::io_service::id id;
  test_service(boost::asio::io_service& s)
    : boost::asio::io_service::service(s) {}
private:
  virtual void shutdown_service() {}
};

boost::asio::io_service::id test_service::id;

void io_service_service_test()
{
  boost::asio::io_service ios1;
  boost::asio::io_service ios2;
  boost::asio::io_service ios3;

  // Implicit service registration.

  boost::asio::use_service<test_service>(ios1);

  BOOST_CHECK(boost::asio::has_service<test_service>(ios1));

  test_service* svc1 = new test_service(ios1);
  try
  {
    boost::asio::add_service(ios1, svc1);
    BOOST_ERROR("add_service did not throw");
  }
  catch (boost::asio::service_already_exists&)
  {
  }
  delete svc1;

  // Explicit service registration.

  test_service* svc2 = new test_service(ios2);
  boost::asio::add_service(ios2, svc2);

  BOOST_CHECK(boost::asio::has_service<test_service>(ios2));
  BOOST_CHECK(&boost::asio::use_service<test_service>(ios2) == svc2);

  test_service* svc3 = new test_service(ios2);
  try
  {
    boost::asio::add_service(ios2, svc3);
    BOOST_ERROR("add_service did not throw");
  }
  catch (boost::asio::service_already_exists&)
  {
  }
  delete svc3;

  // Explicit registration with invalid owner.

  test_service* svc4 = new test_service(ios2);
  try
  {
    boost::asio::add_service(ios3, svc4);
    BOOST_ERROR("add_service did not throw");
  }
  catch (boost::asio::invalid_service_owner&)
  {
  }
  delete svc4;

  BOOST_CHECK(!boost::asio::has_service<test_service>(ios3));
}

test_suite* init_unit_test_suite(int, char*[])
{
  test_suite* test = BOOST_TEST_SUITE("io_service");
  test->add(BOOST_TEST_CASE(&io_service_test));
  test->add(BOOST_TEST_CASE(&io_service_service_test));
  return test;
}
