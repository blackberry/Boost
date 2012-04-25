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
PREFIX=$BOOST_DIR/rim-build/boost-install
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

do_build()
{
    pushd $BOOST_DIR/libs
    for CPU in x86 arm ; do
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
}

# Do a build if the binaries weren't built yet
if [ ! -d $BOOST_DIR/bin.v2 ] ; then
    echo_action "Doing initial build of tests"
    do_build
fi

echo_action "Replacing libraries in $BOOST_DIR/bin.v2"
for FILE in `cat bjam-libs.list` ; do
    if [ `echo "$FILE" | grep -c 'architecture-arm'` -eq 1 ] ; then
        ARCH_DIR='armle-v7'
    elif [ `echo "$FILE" | grep -c 'architecture-x86'` -eq 1 ] ; then
        ARCH_DIR='x86'
    else
        error_exit "Unknown arch: $ARCH"
    fi
    if [ `echo "$FILE" | grep -c 'link-static'` -eq 1 ] ; then
        STATIC=1
        PATTERN='\(\S\+\)\(\.a\)'
    else
        STATIC=0
        PATTERN='\(\S\+\)\(\.so\.\S\+\)'
    fi

    # Only use debug libraries
    DEBUG_NAME=`basename $FILE | sed -e "s|$PATTERN|\1_g\2|"`
    RMAKE_FILE="../rim-build/boost-stage/$ARCH_DIR/usr/lib/$DEBUG_NAME"
    
    if [ ! -f $RMAKE_FILE ] ; then
        echo "Library not found: $RMAKE_FILE"
    else
        # Omit -p option so that the timestamp gets updated
        ${QNX_HOST}/usr/bin/qnx_cp -fcv $RMAKE_FILE ../$FILE
    fi
done

# Build again to link with the rmake-generated libraries
echo_action "Building tests so that they link with rmake-generated libraries"
do_build
