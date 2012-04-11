#!/bin/bash

# Compile every library's test programs

. ../PlayBook-build/env.sh

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

pushd $BOOST_DIR/libs
for TDIR in `cat $TEST_DIR/test.list | grep -v '#'` ; do
    if [ -d $TDIR ] ; then
        pushd $TDIR
        $BJAM -a \
            --prefix=$PREFIX \
            --user-config=$BOOST_DIR/blackberry-armv7le-config.jam \
            --layout=system toolset=qcc target-os=qnxnto \
            c++-template-depth=900 \
            variant=debug link=shared threading=multi
        popd
    fi
done
popd
