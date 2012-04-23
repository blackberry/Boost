#!/bin/bash

# Compile every library's test programs

# ensure required BBNDK env variables are set
: ${QNX_HOST:?"Error: QNX_HOST environment variable is not set."}
: ${QNX_TARGET:?"Error: QNX_TARGET environment variable is not set."}

BOOST_DIR=`pwd`/..
PREFIX=$BOOST_DIR/PlayBook-build/boost-install
if [ ! -d $PREFIX ] ; then
    mkdir -p $PREFIX
fi

pushd $BOOST_DIR
if [ ! -f ./bjam ] ; then
    ./bootstrap.sh
fi
popd

TEST_DIR=`pwd`

BJAM=$BOOST_DIR/bjam

PATTERN='\(\S\+\)\(\(\.so\)\.\S\+\)'
for FILE in `cat libfiles-arm.list` ; do
    DEBUG_NAME=`basename $FILE | sed -e "s|$PATTERN|\1_g\2|"`
    cp ../PlayBook-build/boost-stage/armle-v7/usr/lib/$DEBUG_NAME ../$FILE
done

#for FILE in `cat libfiles-x86.list` ; do
#    DEBUG_NAME=`basename $FILE | sed -e "s|$PATTERN|\1_g\2|"`
#    echo "cp ../PlayBook-build/boost-stage/x86/usr/lib/$DEBUG_NAME $FILE"
#done

pushd $BOOST_DIR/libs
#for CPU in x86 arm ; do
for CPU in arm ; do
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
            # Don't use -a option with bjam as that will cause it 
            # to build the libraries differently from how rmake generates them
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
