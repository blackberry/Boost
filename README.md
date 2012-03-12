
# Blackberry Port of Boost 1.48.0

Officially sanctioned port of Boost to the Blackberry/QNX platform. To avoid fragmentation, please do not use any other version of Boost.

Note there is no official owner for this project. Instead, this project will use an open source development model. If you find a bug in the port, fix it yourself and submit the fix. The port is provided "as is" and without any express or implied warranties.

No Boost shared libraries will be made available on the Blackberry/QNX platform. Anyone that needs a Boost library must use a static version of said library. Since most of Boost exists solely in header files, hopefully, not too many people will need Boost libraries.

Don't like how things are run? Volunteer to become the project owner.

### Prerequisites

- Blackberry Native SDK (NDK) for Tablet OS

### Build Instructions

1. Open a command prompt.
2. Execute bbndk-env.bat or bbndk-env.sh from root of NDK install.
3. Navigate to local boost repo.
4. Execute bootstrap.bat or boostrap.sh.
5. Execute:

        ./bjam install --prefix=<install_path> \
        --user-config=blackberry-<arch>-config.jam --without-python \
        --without-locale --layout=system toolset=qcc target-os=qnxnto
        
        NOTE: <arch> = armv7le | x86

### Notes

- Building from Linux and Windows works. Mac not tested.
- Must clean everything before switching architectures.

### TODO

- Figure out how to run Boost unit tests on device.
- Get Boost.Python and Boost.Locale working.
