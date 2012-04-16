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
for CPU in x86 arm ; do
    if [ "$CPU" == "x86" ] ; then
        CONFIG=$BOOST_DIR/blackberry-x86-config.jam
    elif [ "$CPU" == "arm" ] ; then
        CONFIG=$BOOST_DIR/blackberry-armv7le-config.jam
    else
        echo "Unrecognized CPU ($CPU)."
        exit
    fi 
 
    for TDIR in `cat $TEST_DIR/test.list | grep -v '#'` ; do
        if [ -d $TDIR ] ; then
            pushd $TDIR
            $BJAM \
                --prefix=$PREFIX/$CPU \
                --user-config=$CONFIG \
                --layout=system toolset=qcc target-os=qnxnto architecture=$CPU \
                c++-template-depth=900 \
                variant=debug link=shared threading=multi
            popd
        fi
    done
done
popd
