#ifndef BOOST_SMART_PTR_DETAIL_SPINLOCK_GCC_ARM_HPP_INCLUDED
#define BOOST_SMART_PTR_DETAIL_SPINLOCK_GCC_ARM_HPP_INCLUDED

//
//  Copyright (c) 2008 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#include <boost/smart_ptr/detail/yield_k.hpp>

#if defined(__ARM_ARCH_2__) || defined(__ARM_ARCH_3__) || defined(__ARM_ARCH_3M__) || \
    defined(__ARM_ARCH_4__) || defined(__ARM_ARCH_4T__) || defined(__ARM_ARCH_5__) || \
    defined(__ARM_ARCH_5E__) || defined(__ARM_ARCH_5T__) || defined(__ARM_ARCH_5TE__) || \
    defined(__ARM_ARCH_5TEJ__) || defined(__ARM_ARCH_6__) || defined(__ARM_ARCH_6J__) || \
    defined(__ARM_ARCH_6K__) || defined(__ARM_ARCH_6Z__) || defined(__ARM_ARCH_6ZK__) || \
    defined(__ARM_ARCH_6T2__)
#define BOOST_PRE_ARMV7
#endif

namespace boost
{

namespace detail
{

class spinlock
{
public:

    int v_;

public:

bool try_lock()
    {
#if defined(BOOST_PRE_ARMV7)
        int r;

        __asm__ __volatile__(
            "swp %0, %1, [%2]":   // r = old value of v_, v_ = 1, atomically
            "=&r"( r ): // outputs
            "r"( 1 ), "r"( &v_ ): // inputs
            "memory", "cc" );

        // if v_ was 0 before we set it, then we got the lock
        // (otherwise we set it to 1, but it already was 1)
        // note that in this implementation, it means either way, someone has/had the lock,
        // but you shouldn't rely on that (see ARMV7 implementation)
        return r == 0;
#else
        int r, tmp;

        __asm__ __volatile__(
            "ldrex %0, [%3];"      // r = v_
            "strex %1, %2, [%3];"  // try v_ = 1; tmp = !success
            "dmb;"                 // note: probably should only do this if lock succeeds
            : "=&r"( r ), "=&r"( tmp ) // outputs
            : "r"( 1 ), "r"( &v_ ) // inputs
            : "memory", "cc" );

        // return true iff lock was 0 && we successfully set it to 1
        // (subtle note: so try_lock() == 0 does NOT mean someone else has (or just had a few instructions ago) the lock,
        //  it just means we could NOT get it.
        //  It may actually have been some other bus/memory reason
        //  and our attempt just failed, even though the lock was 0.
        //  So failure does NOT imply that someone else has/had the lock.
        //  This is called 'spurious failure' and is allowed by C++11 try_lock spec
        //  (which I assume this try_lock is trying to match).)
        return r == 0 && tmp == 0;
#endif
    }

    void lock()
    {
        for( unsigned k = 0; !try_lock(); ++k )
        {
            boost::detail::yield( k );
        }
    }

    void unlock()
    {
#if defined(BOOST_PRE_ARMV7)
        __asm__ __volatile__( "" ::: "memory" );
#else
        __asm__ __volatile__( "dmb" ::: "memory" );
#endif
        *const_cast< int volatile* >( &v_ ) = 0;
    }

public:

    class scoped_lock
    {
    private:

        spinlock & sp_;

        scoped_lock( scoped_lock const & );
        scoped_lock & operator=( scoped_lock const & );

    public:

        explicit scoped_lock( spinlock & sp ): sp_( sp )
        {
            sp.lock();
        }

        ~scoped_lock()
        {
            sp_.unlock();
        }
    };
};

} // namespace detail
} // namespace boost

#define BOOST_DETAIL_SPINLOCK_INIT {0}

#endif // #ifndef BOOST_SMART_PTR_DETAIL_SPINLOCK_GCC_ARM_HPP_INCLUDED
