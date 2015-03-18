Boost for BlackBerry 10
-----------------------

Current Boost Version: 1.57.0.

For the most part, Boost requires almost _no_ changes to work in BlackBerry 10 ("BB10").  All required code changes are pushed upstream whenever possible.


What isn't upstreamed is how to build it, as it is BB10 specific.  That can be found here.

In particular, there is a `blackberry-config.jam` that helps build Boost for the device.
There is also a simple `bbbb` script (`bbbb.sh` or `bbbb.bat`) to Build Boost for BlackBerry.  Basically the script shows the required command bjam command line for building boost.


Requirements
------------

You must have the BB10 NDK setup in order to build Boost for BB10.  It can be downloaded at <http:://developer.blackberry.com>.
The BB10 NDK needs to be in your path for the boost build to work.  (ie use the `bbndk-env` script to help with that.)


Build Instructions
------------------

1. run bbndk-env (.bat or .sh) to set up the BB10 NDK environment variables.
1. run bootstrap (.bat or .sh) as you normally would to get Boost.Build set up.
1. (optional) build Boost for your host platform, to check that everything is set up correctly.
1. run bbbb (.bat or .sh) to build Boost for BlackBerry10.

Tests
-----

Currently, it is not easy to run the tests to verify boost was built correctly.  (This is because the tests need to run on device, not locally, and doing that is a bit tricky...)

Note this means much of the boost is untested on BB10 (although much of it is used internally by BlackBerry and tested by other means).


Known Caveats
-------------

Boost.Context probably doesn't work on QNX/BB10.
Boost.Python only works if you can find a version of python for QNX. (ie find a version of python for linux and you are close, but you will need to build it yourself for QNX.)


Repository Committers
---------------------

* [Eduardo Pelegri-Llopart](https://github.com/pelegri)
* [Clifford Hung](https://github.com/hungc)
* [Tony Van Eerd](https://github.com/tvaneerd-rim)


Bug Reporting and Feature Requests
----------------------------------


If you find a bug or have an enhancement request, simply file an [Issue](https://github.com/blackberry/Boost/issues) and send a message (via github messages) to the Committers to the project to let them know that you have filed an [Issue](https://github.com/blackberry/Boost/issues).


Disclaimer
----------

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


