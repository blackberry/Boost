#!/bin/bash

# Compile every library's test programs

# ensure required BBNDK env variables are set
: ${QNX_HOST:?"Error: QNX_HOST environment variable is not set."}
: ${QNX_TARGET:?"Error: QNX_TARGET environment variable is not set."}

TEST_DIR=`pwd`
BOOST_DIR=`pwd`/..
PREFIX=$BOOST_DIR/PlayBook-build/boost-install
if [ ! -d $PREFIX ] ; then
    echo "Couldn't find prefix $PREFIX"
    exit
fi

BJAM=$BOOST_DIR/bjam
PYTHON_SRC=/home/chung/dev/product-rim/trunk/tools/python-3.2

pushd $BOOST_DIR/libs
pwd
for TDIR in `cat $TEST_DIR/test.list | grep -v '#'` ; do
pwd
    pushd $TDIR
    $BJAM \
        include="$PYTHON_SRC/Include:$PYTHON_SRC" \
        --prefix=$PREFIX \
        --user-config=$BOOST_DIR/blackberry-armv7le-config.jam \
        --layout=system toolset=qcc target-os=qnxnto
    popd
done
popd
