#!/bin/sh

# Run every library's test programs

# Use "./run-tests.sh 2>1 > run-tests.out" to redirect both stdout and
# stderr to an output file

usage()
{
    echo "$0 <arm|x86>"
}

if [ $# -ne 1 ] ; then
    usage
    exit
fi

ARCH=$1
if [ "$ARCH" != "arm" ] && [ "$ARCH" != "x86" ] ; then
    usage
    exit
fi

TEST_DIR=`pwd`
BOOST_DIR=`pwd`/..

cd $BOOST_DIR

# Use the same list of test directories that the build script uses
for TDIR in `cat $TEST_DIR/test.list | grep -v '#'` ; do
    # Get the base path of the tests
    EXE_DIR=`echo $TDIR | sed -e 's|^.\/\(.\+\)$|bin.v2\/libs\/\1|'`
    find $EXE_DIR -perm -001 -type f -a ! -name 'libboost_*' > $TEST_DIR/find-exe.list
    for EXE_PATH in `cat $TEST_DIR/find-exe.list | grep -v '#' | grep $ARCH` ; do
        LIB_DIR=`echo $TDIR | sed -e 's|^.\/\(.\+\)$|libs\/\1|'`
        
        # Find executable files in the dir
        if [ -d $LIB_DIR ] ; then
            cd $LIB_DIR
        else
            echo "LIB_DIR ($LIB_DIR) not found for $EXE_PATH"
            continue
        fi 
        EXE_CMD="$BOOST_DIR/$EXE_PATH"
        echo "Running $EXE_CMD"
        $EXE_CMD
        RET=$?
        echo "$EXE_CMD returned $RET"
        cd $BOOST_DIR
    done
done
cd $TEST_DIR
