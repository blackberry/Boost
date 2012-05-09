#!/bin/bash

# Compile every library's test programs

# ensure required BBNDK env variables are set
: ${QNX_HOST:?"Error: QNX_HOST environment variable is not set."}
: ${QNX_TARGET:?"Error: QNX_TARGET environment variable is not set."}

error_exit()
{
   echo "Error: $1"
   exit 
}

echo_action()
{
    echo "===> $1"
}

BOOST_DIR=`pwd`/..

pushd $BOOST_DIR
if [ ! -f ./bjam ] ; then
    ./bootstrap.sh
fi
popd

TEST_DIR=`pwd`

BJAM=$BOOST_DIR/bjam

do_build()
{
    pushd $BOOST_DIR/libs
    for CPU in arm x86 ; do
        if [ "$CPU" == "x86" ] ; then
            CONFIG=$BOOST_DIR/blackberry-x86-config.jam
        elif [ "$CPU" == "arm" ] ; then
            CONFIG=$BOOST_DIR/blackberry-armv7le-config.jam
        else
            error_exit "Unrecognized CPU ($CPU)."
        fi 
     
        for TDIR in `cat $TEST_DIR/test.list | grep -v '#'` ; do
            if [ -d $TDIR ] ; then
                pushd $TDIR
                # Disable builds with ICU because the ICU libraries are linked against Dinkumware libraries.
                # This will cause crashes because GNU and Dinkumware libraries cannot be mixed.
                $BJAM  \
                    -j 4 \
                    --disable-icu \
                    --user-config=$CONFIG \
                    --layout=system toolset=qcc target-os=qnxnto architecture=$CPU \
                    c++-template-depth=900 \
                    variant=debug link=shared threading=multi
                popd
            fi
        done
    done
    popd
}

echo_action "Building tests"
do_build
