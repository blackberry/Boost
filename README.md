# Blackberry Port of Boost 1.48.0

Port of Boost to the Blackberry platform for use with GNU C++ libraries.

### Prerequisites

- Blackberry Native SDK (NDK) for Tablet OS

### Build Instructions

1. Open a Linux command prompt.
2. Source bbndk-env.sh from the root of NDK install.
3. Navigate to local boost repo and go into the rim-build directory.
4. Run the build script: "build.sh install". This will generate
    and install release and debug libraries for ARM and X86 in the 
    rim-build/boost-stage directory.

### Notes

- Boost libraries that are required for your application need to be included in your BAR file. Any Boost libraries
    that may be found on the device will be using Dinkumware C++ libraries and are not compatible with GNU C++ libraries.

- The following libraries compile and the tests pass (with a few exceptions noted below) on ARM and X86:
    date_time
    filesystem
    program_options
    random
    regex
    system
    thread

- Building from Linux works. Windows and Mac not tested.

### Known compilation and test failures for ported libraries:

- boost/libs/thread/test/test_thread_return_local.cpp fails to compile but the same
error happens on Linux (gcc-4.6.1)
- boost/bin.v2/libs/optional/test/optional_test_ref.test fails with the same error as on Linux
- boost/bin.v2/libs/program_options/test/qcc/debug/link-static/target-os-qnxnto/test_convert fails with the same output as on Linux
- boost/bin.v2/libs/ptr_container/test/serialization.test/qcc/debug/target-os-qnxnto/serialization fails with the same output as on Linux

### TODO

- Fix compilation and test errors for other libraries.
