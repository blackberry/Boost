//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2004-2009. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/containers/pair.hpp>
#include "movable_int.hpp"
#include "emplace_test.hpp"
#include<boost/move/move.hpp>

//non_copymovable_int
//copyable_int
//movable_int
//movable_and_copyable_int


using namespace ::boost::interprocess;

int main ()
{
   {
      pair<test::non_copymovable_int, test::non_copymovable_int> p1;
      pair<test::copyable_int, test::copyable_int> p2;
      pair<test::movable_int, test::movable_int> p3;
      pair<test::movable_and_copyable_int, test::movable_and_copyable_int> p4;
   }
   {  //Constructible from two values
      pair<test::non_copymovable_int, test::non_copymovable_int> p1(1, 2);
      pair<test::copyable_int, test::copyable_int> p2(1, 2);
      pair<test::movable_int, test::movable_int> p3(1, 2);
      pair<test::movable_and_copyable_int, test::movable_and_copyable_int> p4(1, 2);
   }

   {  //Constructible from internal types
      pair<test::copyable_int, test::copyable_int> p2(test::copyable_int(1), test::copyable_int(2));
      {
         test::movable_int a(1), b(2);
         pair<test::movable_int, test::movable_int> p3(::boost::move(a), ::boost::move(b));
      }
      {
         test::movable_and_copyable_int a(1), b(2);
         pair<test::movable_and_copyable_int, test::movable_and_copyable_int> p4(::boost::move(a), ::boost::move(b));
      }
   }
   //piecewise_construct missing...
   return 0;
}

#include <boost/interprocess/detail/config_end.hpp>
