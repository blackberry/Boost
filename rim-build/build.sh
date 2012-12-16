#!/bin/bash

# ensure required BBNDK env variables are set
: ${QNX_HOST:?"Error: QNX_HOST environment variable is not set."}
: ${QNX_TARGET:?"Error: QNX_TARGET environment variable is not set."}

# Get absolute path of script
SCRIPT_PATH=$PWD/$BASH_SOURCE
SCRIPT_DIR=`dirname $SCRIPT_PATH`

# Set to Python source location when building Python library
PYTHON_SRC_DIR=""

pushd $SCRIPT_DIR

usage()
{
    echo "$0 <install|clean> <static|shared>"
}

echo_action()
{
    echo "===> $1"
}

build()
{
    if [ "$ACTION" == "clean" ] ; then
        if [ "$PREFIX" != "/" ] && [ -n $PREFIX ] ; then
            rm -rf $PREFIX
        fi
    fi

    pushd $BOOST_DIR
    if [ ! -f ./bjam ] ; then
        ./bootstrap.sh
    fi

    # Build the libraries and install them to staging dir
    for CPU in arm x86 ; do
        if [ "$CPU" == "x86" ] ; then
            CONFIG=$BOOST_DIR/blackberry-x86-config.jam
            CPU_DIR="x86"
        elif [ "$CPU" == "arm" ] ; then
            CONFIG=$BOOST_DIR/blackberry-armv7le-config.jam
            CPU_DIR="armle-v7"
        else
            echo "Unrecognized CPU ($CPU)."
            exit
        fi 

        for VARIANT in debug release ; do
            echo_action "Building $CPU $VARIANT"
            if [ "$ACTION" == "install" ] ; then
                # bjam will append the lib directory
                BJAM_ARGS="stage --stagedir=$PREFIX/$CPU_DIR/$VARIANT"
            elif [ "$ACTION" == "clean" ] ; then
                BJAM_ARGS="--clean"
            fi

            if [ "$VARIANT" == "release" ] ; then
                BJAM_ARGS="$BJAM_ARGS optimization=space"
            fi

            if [ "$PYTHON_SRC_DIR" != "" ] && [ -d $PYTHON_SRC_DIR ] ; then
                BJAM_ARGS="$BJAM_ARGS include=$PYTHON_SRC_DIR:$PYTHON_SRC_DIR/Include --with-python"
            fi

            # Disable builds with ICU because the ICU libraries are linked against Dinkumware libraries.
            # This will cause crashes because GNU and Dinkumware libraries cannot be mixed.
            ./bjam $BJAM_ARGS \
                -j 4 \
                --disable-icu \
                --with-chrono \
                --with-date_time \
                --with-exception \
                --with-filesystem \
                --with-graph \
                --with-graph_parallel \
                --with-iostreams \
                --with-locale \
                --with-math \
                --with-mpi \
                --with-program_options \
                --with-random \
                --with-regex \
                --with-serialization \
                --with-signals \
                --with-system \
                --with-test \
                --with-thread \
                --with-timer \
                --with-wave \
                --user-config=$CONFIG \
                --layout=system toolset=qcc target-os=qnxnto architecture=$CPU \
                variant=$VARIANT link=$LINK_TYPE threading=multi runtime-link=shared
        done
    done
    popd
}

#########################################################
# Begin main script
#########################################################

if [ $# -lt 1 ] ; then
    usage
    exit
fi

ACTION=$1
if [ "$ACTION" != "install" ] && [ "$ACTION" != "clean" ] ; then
    usage
    exit
fi

LINK_TYPE=$2
if [ "$LINK_TYPE" != "static" ] && [ "$LINK_TYPE" != "shared" ] ; then
    usage
    exit
fi

BOOST_DIR="`pwd`/.."

PREFIX=`pwd`/boost-stage
if [ ! -d $PREFIX ] ; then
    mkdir -p $PREFIX
fi

echo "build $ACTION $LINK_TYPE"
build
