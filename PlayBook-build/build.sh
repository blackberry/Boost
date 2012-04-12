#!/bin/bash

. ./env.sh

# ensure required BBNDK env variables are set
: ${QNX_HOST:?"Error: QNX_HOST environment variable is not set."}
: ${QNX_TARGET:?"Error: QNX_TARGET environment variable is not set."}

PREFIX=`pwd`/boost-install
if [ ! -d $PREFIX ] ; then
    mkdir -p $PREFIX
fi

pushd ..
BOOST_DIR=`pwd`

if [ ! -f ./bjam ] ; then
    ./bootstrap.sh
fi

# Build the libraries required by RIM teams
for CPU in arm x86 ; do
    if [ "$CPU" == "x86" ] ; then
        CONFIG=$BOOST_DIR/blackberry-x86-config.jam
    elif [ "$CPU" == "arm" ] ; then
        CONFIG=$BOOST_DIR/blackberry-armv7le-config.jam
    else
        echo "Unrecognized CPU ($CPU)."
        exit
    fi 

    pushd $BOOST_DIR/libs/test/build
    # Build libboost_test
    cp Jamfile-rim.v2 Jamfile.v2
    $BOOST_DIR/bjam -a stage \
        --user-config=$CONFIG \
        --layout=system toolset=qcc target-os=qnxnto \
        variant=debug link=shared threading=multi

        # Copy needed library files to real staging dir (don't move them because asio tests need to link against them there)
        cp stage/libboost_test.so* $PREFIX/$CPU/debug/lib

    # Restore original Jamfile
    cp Jamfile-orig.v2 Jamfile.v2
    popd

    for VARIANT in debug release ; do
        ./bjam -a stage \
            --stagedir=$PREFIX/$CPU/$VARIANT \
            --with-date_time \
            --with-filesystem \
            --disable-filesystem2 \
            --with-program_options \
            --with-random \
            --with-regex \
            --with-system \
            --with-thread \
            --user-config=$CONFIG \
            --layout=system toolset=qcc target-os=qnxnto \
            variant=$VARIANT link=shared threading=multi runtime-link=shared
    done

done
popd

# Copy needed header files
if [ ! -d $PREFIX/include ] ; then
    mkdir $PREFIX/include
fi
echo "Copying include files"

for INC_FILE in `cat headers.txt` ; do
    INC_DIR=`dirname $INC_FILE`
    if [ ! -d $PREFIX/include/$INC_DIR ] ; then
        mkdir -p $PREFIX/include/$INC_DIR 
    fi
    cp $BOOST_DIR/$INC_FILE $PREFIX/include/$INC_DIR
done
