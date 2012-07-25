# Blackberry Port of Boost 1.48.0

Port of Boost to the BlackBerry 10 platform.

Ported libraries:

- *Boost.Date_Time
- Boost.Filesystem
- Boost.Program_options
- Boost.Random
- *Boost.Regex
- Boost.System
- Boost.Thread

Ported headers:

- Listed in boost/include/headers.txt

Note: there a few unresolved test failures involving `Boost.Date_Time` and `Boost.Regex` See the "Known issues with tests" section.

## Prerequisites

- Blackberry Native SDK (NDK) for Tablet OS

## Build Instructions

1. Open a command prompt (building from Linux and Windows works; Mac has not been tested).
2. Execute bbndk-env.bat or bbndk-env.sh from root of NDK install.
3. Navigate to local boost repo.
4. Change to the rim-build directory. The build.sh script can build static or dynamic libraries. For example, to build dynamic libraries, use this command:

        ./build.sh install dynamic

    This will invoke the bjam executable to build the libraries in subdirectories of bin.v2 as well as copy them to a staging directory (under rim-build/boost-stage).

    All the libraries are compiled, not just the ported ones. The Boost.Python library can be enabled by setting the `PYTHON_SRC_DIR` variable in build.sh to the Python source location.

    Use `./build.sh clean <static|dynamic>` to clean the build.

## Test Instructions

1. Change to the rim-test directory.
2. Run the build-tests.sh script which will invoke bjam on each test directory read from the test.list file. You can choose to skip some tests by commenting them out with a "#". The build script will build and attempt to run the tests. The test failures can be ignored since they aren't being run on a BB 10 device.
3. The test binaries can either be copied over to a device in development mode (using scp) or the top-level boost directory can be NFS-mounted on the device. It will be easier to recompile and rerun tests with the latter setup but some of the filesystem tests may fail due to issues with NFS. NFS setup instructions are below.
4. To run the tests, go to /accounts/devuser/boost and run the run-tests.sh script:

        ./run-tests.sh <arm|x86> 2> run.err > run.out &

    Use the tail command to observe the progress of the tests, e.g. `tail -f run.out`.

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

### Known issues with tests

Some of the filesystem tests may fail when run from an NFS mount.

Failures for Boost.Date_Time:

    bin.v2/libs/date_time/test/teststreams.test/qcc/debug/architecture-arm/target-os-qnxnto/threading-multi/teststreams

Failures for Boost.Regex:

    bin.v2/libs/regex/test/regex_regress_recursive.test/qcc/debug/architecture-arm/target-os-qnxnto/threading-multi/regex_regress_recursive
    bin.v2/libs/regex/test/regex_regress_threaded.test/qcc/debug/architecture-arm/target-os-qnxnto/threading-multi/regex_regress_threaded
    bin.v2/libs/regex/test/regex_regress.test/qcc/debug/architecture-arm/target-os-qnxnto/threading-multi/regex_regress

## Repository Committers

* [Eduardo Pelegri-Llopart](https://github.com/pelegri)
* [Clifford Hung](https://github.com/hungc)


## Bug Reporting and Feature Requests

If you find a bug or have an enhancement request, simply file an [Issue](https://github.com/blackberry/Boost/issues) and send a message (via github messages) to the Committers to the project to let them know that you have filed an [Issue](https://github.com/blackberry/Boost/issues).

## Disclaimer

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
