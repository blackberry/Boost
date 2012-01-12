//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2004-2011. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#include <boost/container/detail/config_begin.hpp>
#include <set>
#include <boost/container/set.hpp>
#include <boost/container/map.hpp>
#include "print_container.hpp"
#include "movable_int.hpp"
#include "dummy_test_allocator.hpp"
#include "set_test.hpp"
#include "map_test.hpp"
#include "emplace_test.hpp"

using namespace boost::container;

//Alias standard types
typedef std::set<int>                                          MyStdSet;
typedef std::multiset<int>                                     MyStdMultiSet;
typedef std::map<int, int>                                     MyStdMap;
typedef std::multimap<int, int>                                MyStdMultiMap;

//Alias non-movable types
typedef set<int>           MyBoostSet;
typedef multiset<int>      MyBoostMultiSet;
typedef map<int, int>      MyBoostMap;
typedef multimap<int, int> MyBoostMultiMap;

//Alias movable types
typedef set<test::movable_int>                           MyMovableBoostSet;
typedef multiset<test::movable_int>                      MyMovableBoostMultiSet;
typedef map<test::movable_int, test::movable_int>        MyMovableBoostMap;
typedef multimap<test::movable_int, test::movable_int>   MyMovableBoostMultiMap;
typedef set<test::movable_and_copyable_int>              MyMoveCopyBoostSet;
typedef set<test::copyable_int>                          MyCopyBoostSet;
typedef multiset<test::movable_and_copyable_int>         MyMoveCopyBoostMultiSet;
typedef multiset<test::copyable_int>                     MyCopyBoostMultiSet;
typedef map<test::movable_and_copyable_int
           ,test::movable_and_copyable_int>              MyMoveCopyBoostMap;
typedef multimap<test::movable_and_copyable_int
                ,test::movable_and_copyable_int>         MyMoveCopyBoostMultiMap;
typedef map<test::copyable_int
           ,test::copyable_int>                          MyCopyBoostMap;
typedef multimap<test::copyable_int
                ,test::copyable_int>                     MyCopyBoostMultiMap;
//Test recursive structures
class recursive_set
{
public:
   int id_;
   set<recursive_set> set_;
   friend bool operator< (const recursive_set &a, const recursive_set &b)
   {  return a.id_ < b.id_;   }
};

class recursive_map
{
   public:
   int id_;
   map<recursive_map, recursive_map> map_;
   friend bool operator< (const recursive_map &a, const recursive_map &b)
   {  return a.id_ < b.id_;   }
};

//Test recursive structures
class recursive_multiset
{
public:
   int id_;
   multiset<recursive_multiset> multiset_;
   friend bool operator< (const recursive_multiset &a, const recursive_multiset &b)
   {  return a.id_ < b.id_;   }
};

class recursive_multimap
{
public:
   int id_;
   multimap<recursive_multimap, recursive_multimap> multimap_;
   friend bool operator< (const recursive_multimap &a, const recursive_multimap &b)
   {  return a.id_ < b.id_;   }
};

template<class C>
void test_move()
{
   //Now test move semantics
   C original;
   C move_ctor(boost::move(original));
   C move_assign;
   move_assign = boost::move(move_ctor);
   move_assign.swap(original);
}

int main ()
{
   //Recursive container instantiation
   {
      set<recursive_set> set_;
      multiset<recursive_multiset> multiset_;
      map<recursive_map, recursive_map> map_;
      multimap<recursive_multimap, recursive_multimap> multimap_;
   }
   //Now test move semantics
   {
      test_move<set<recursive_set> >();
      test_move<multiset<recursive_multiset> >();
      test_move<map<recursive_map, recursive_map> >();
      test_move<multimap<recursive_multimap, recursive_multimap> >();
   }

   //using namespace boost::container::detail;

   if(0 != test::set_test<MyBoostSet
                        ,MyStdSet
                        ,MyBoostMultiSet
                        ,MyStdMultiSet>()){
      return 1;
   }

   if(0 != test::set_test_copyable<MyBoostSet
                        ,MyStdSet
                        ,MyBoostMultiSet
                        ,MyStdMultiSet>()){
      return 1;
   }

   if(0 != test::set_test<MyMovableBoostSet
                        ,MyStdSet
                        ,MyMovableBoostMultiSet
                        ,MyStdMultiSet>()){
      return 1;
   }

   if(0 != test::set_test<MyMoveCopyBoostSet
                        ,MyStdSet
                        ,MyMoveCopyBoostMultiSet
                        ,MyStdMultiSet>()){
      return 1;
   }

   if(0 != test::set_test_copyable<MyMoveCopyBoostSet
                        ,MyStdSet
                        ,MyMoveCopyBoostMultiSet
                        ,MyStdMultiSet>()){
      return 1;
   }

   if(0 != test::set_test<MyCopyBoostSet
                        ,MyStdSet
                        ,MyCopyBoostMultiSet
                        ,MyStdMultiSet>()){
      return 1;
   }

   if(0 != test::set_test_copyable<MyCopyBoostSet
                        ,MyStdSet
                        ,MyCopyBoostMultiSet
                        ,MyStdMultiSet>()){
      return 1;
   }

   if (0 != test::map_test<MyBoostMap
                  ,MyStdMap
                  ,MyBoostMultiMap
                  ,MyStdMultiMap>()){
      return 1;
   }

   if(0 != test::map_test_copyable<MyBoostMap
                        ,MyStdMap
                        ,MyBoostMultiMap
                        ,MyStdMultiMap>()){
      return 1;
   }

//   if (0 != test::map_test<my_managed_shared_memory
//                  ,MyMovableBoostMap
//                  ,MyStdMap
//                  ,MyMovableBoostMultiMap
//                  ,MyStdMultiMap>()){
//      return 1;
//   }

   if (0 != test::map_test<MyMoveCopyBoostMap
                  ,MyStdMap
                  ,MyMoveCopyBoostMultiMap
                  ,MyStdMultiMap>()){
      return 1;
   }

   if (0 != test::map_test_copyable<MyMoveCopyBoostMap
                  ,MyStdMap
                  ,MyMoveCopyBoostMultiMap
                  ,MyStdMultiMap>()){
      return 1;
   }

   if (0 != test::map_test<MyCopyBoostMap
                  ,MyStdMap
                  ,MyCopyBoostMultiMap
                  ,MyStdMultiMap>()){
      return 1;
   }

   if (0 != test::map_test_copyable<MyCopyBoostMap
                  ,MyStdMap
                  ,MyCopyBoostMultiMap
                  ,MyStdMultiMap>()){
      return 1;
   }

   const test::EmplaceOptions SetOptions = (test::EmplaceOptions)(test::EMPLACE_HINT | test::EMPLACE_ASSOC);
   if(!boost::container::test::test_emplace<set<test::EmplaceInt>, SetOptions>())
      return 1;
   if(!boost::container::test::test_emplace<multiset<test::EmplaceInt>, SetOptions>())
      return 1;
   const test::EmplaceOptions MapOptions = (test::EmplaceOptions)(test::EMPLACE_HINT_PAIR | test::EMPLACE_ASSOC_PAIR);
   if(!boost::container::test::test_emplace<map<test::EmplaceInt, test::EmplaceInt>, MapOptions>())
      return 1;
   if(!boost::container::test::test_emplace<multimap<test::EmplaceInt, test::EmplaceInt>, MapOptions>())
      return 1;

   return 0;
}

#include <boost/container/detail/config_end.hpp>
