//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// Copyright (C) 2011 Vicente J. Botet Escriba
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// <boost/thread/future.hpp>

// class packaged_task<R>

// ~packaged_task();
;

#define BOOST_THREAD_VERSION 3

#include <boost/thread/future.hpp>
#include <boost/thread/thread.hpp>
#include <boost/detail/lightweight_test.hpp>

class A
{
    long data_;

public:
    explicit A(long i) : data_(i) {}

    long operator()() const {return data_;}
    long operator()(long i, long j) const {return data_ + i + j;}
};

void func(boost::packaged_task<double> p)
{
}

void func2(boost::packaged_task<double> p)
{
  //p(3, 'a');
  p();
}

int main()
{
  {
      boost::packaged_task<double> p(A(5));
      boost::future<double> f = BOOST_THREAD_MAKE_RV_REF(p.get_future());
      boost::thread(func, boost::move(p)).detach();
      try
      {
          double i = f.get();
          BOOST_TEST(false);
      }
      catch (const boost::future_error& e)
      {
          BOOST_TEST(e.code() == boost::system::make_error_code(boost::future_errc::broken_promise));
      }
  }
  {
      boost::packaged_task<double> p(A(5));
      boost::future<double> f = BOOST_THREAD_MAKE_RV_REF(p.get_future());
      boost::thread(func2, boost::move(p)).detach();
      BOOST_TEST(f.get() == 5.0);
  }


  return boost::report_errors();
}

