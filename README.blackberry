--------------------------------------------------------------------------
Blackberry Port of Boost 1.48.0
--------------------------------------------------------------------------

Prerequisites:
- Blackberry Native SDK (NDK) for Tablet OS

Build Instructions
1. Open a command prompt.
2. Execute bbndk-env.bat or bbndk-env.sh from root of NDK install.
3. Navigate to local boost repo.
4. Execute bootstrap.bat or boostrap.sh.
5. Execute: ./bjam install --prefix=<install_path> \
            --user-config=blackberry-<arch>-config.jam --without-python \
            --without-locale --layout=system toolset=qcc target-os=qnxnto

   (Device build: <arch> = "armv7le", Simulator build: <arch> = "x86")

Notes:
- Building from Linux and Windows works. Mac not tested.
- Must clean everything before switching architectures.

TODO:
- Figure out how to run Boost unit tests on device.
- Get Boost.Python and Boost.Locale working.
