

Boost for BlackBerry 10
-----------------------

Boost requires almost _no_ changes to work in BlackBerry 10 ("BB10").  All required code changes are pushed upstream whenever possible.

Note, however, that a few modules (ie Context) may not yet work in BB10.


What isn't upstreamed is how to build it, as it is BB10 specific.  That can be found here.

In particular, there is a blackberry-config.jam that helps build Boost for the device.
There is also a simple 'bbbb' script (.sh or .bat) to Build Boost for BlackBerry.  Basically the script shows the required command bjam command line for building boost.


Requirements
------------

You must have the BB10 NDK setup in order to build Boost for BB10.  It can be downloaded at http:://developer.blackberry.com.
The BB10 NDK needs to be in your path for the boost build to work.  (ie use the bbndk-env script to help with that.)


Tests
-----

Currently, it is not easy to run the tests to verify boost was built correctly.  (This is because the tests need to run on device, not locally, and doing that is a bit tricky...)

Note this means much of the boost is untested on BB10 (although much of it is used internally by BlackBerry and tested by other means).


