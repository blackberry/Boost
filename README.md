# Blackberry Port of Boost 1.48.0

Officially sanctioned port of Boost to the Blackberry/QNX platform. To avoid fragmentation, please do not use any other version of Boost. Before you use Boost make sure Qt does not already provide equivalent functionality as Qt should always be prefered over Boost. Furthermore, do not expose any Boost constructs in public APIs.

Please direct all inquiries about Boost to Steven Chan (schan@rim.com).

Ported libraries:

- Boost.Date_Time
- Boost.Filesystem
- Boost.Program_options
- Boost.Random
- Boost.Regex
- Boost.System
- Boost.Thread

Ported headers:

- Listed in boost/include/headers.txt

### Prerequisites

- Blackberry Native SDK (NDK) for Tablet OS

### Build Instructions

1. Open a command prompt.
2. Execute bbndk-env.bat or bbndk-env.sh from root of NDK install.
3. Navigate to local boost repo.
4. Run `make`. This will create libraries under each library's build directory, for example, the filesystem library is built under libs/filesystem/build for ARM and X86. For building the tests, the libraries need to be copied to a staging directory using the following command:

        make install INSTALL_ROOT_nto=<Path to boost repo>/rim-build/boost-stage

    Partial builds can be accomplished using the LIST tag found in the makefiles. For example, you could build debug ARM libraries by running this command:

        make CPULIST=arm VARIANTLIST=g

    Use `make clean` to clean the build.

### Test Instructions

1. Change to the rim-test directory.
2. Run the build-tests.sh script which will invoke bjam on each test directory read from the test.list file. You can choose to skip some tests by commenting them out with a "#". The build script will build and attempt to run the tests. The test failures can be ignored since they aren't being run on a BB 10 device.
3. The test binaries can either be copied over to a device in development mode (using scp) or the top-level boost directory can be NFS-mounted on the device. It will be easier to recompile and rerun tests with the latter setup but some of the filesystem tests may fail due to issues with NFS. NFS setup instructions are below.
4. To run the tests, go to /accounts/devuser/boost and run the run-tests.sh script:

        ./run-tests.sh 2> run.err > run.out &

    The tail command to observe the progress of the tests, e.g. `tail -f run.out`.

### NFS setup for Ubuntu Linux and PlayBook over USB (optional)

1. On your Linux machine, obtain the packages to install the NFS server:

        sudo apt-get install nfs-kernel-server nfs-common portmap

2. Edit the NFS exports file as follows:

        sudo vi /etc/exports

3. Add the following line:

        <Path to boost repo> 169.254.0.1(rw,all_squash,async,insecure,no_subtree_check,anonuid=<UID>,anongid=<GID>)

4. Make the NFS server reread the configuration:

        sudo service nfs-kernel-server reload

5. On the PlayBook, issue the following command to mount the NFS-exported directory:

        fs-nfs3 169.254.0.2:<Path to boost repo on server> /accounts/devuser/boost

### Notes

- Building from Linux and Windows works. Mac not tested.

### TODO

- Port other headers and libraries
