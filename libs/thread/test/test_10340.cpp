#define BOOST_THREAD_VERSION 4

#include <boost/thread/future.hpp>

struct foo
{
    foo(int i_): i(i_) {}
    int i;
};

int main()
{
  boost::promise<foo> p;
  const foo f(42);
  p.set_value(f);

  // Clearly a const future ref isn't much use, but I needed to
  // prove the problem wasn't me trying to copy a unique_future

  const boost::future<foo>& fut = boost::make_ready_future( foo(42) );
  return 0;
}

