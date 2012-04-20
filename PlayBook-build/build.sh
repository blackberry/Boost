#!/bin/bash

# ensure required BBNDK env variables are set
: ${QNX_HOST:?"Error: QNX_HOST environment variable is not set."}
: ${QNX_TARGET:?"Error: QNX_TARGET environment variable is not set."}

# Get absolute path of script
SCRIPT_PATH=$PWD/$BASH_SOURCE
SCRIPT_DIR=`dirname $SCRIPT_PATH`

pushd $SCRIPT_DIR

usage()
{
    echo "$0 <install|hinstall|clean>"
}

build()
{
    ARG=$1

    if [ "$ACTION" == "clean" ] ; then
        if [ "$PREFIX" != "/" ] && [ -n $PREFIX ] ; then
            rm -rf $PREFIX
        fi
    fi

    pushd $BOOST_DIR
    if [ ! -f ./bjam ] ; then
        ./bootstrap.sh
    fi

    # Build the libraries required by RIM teams
    # and install them to staging dir
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
            if [ "$ARG" == "install" ] ; then
                # bjam will append the lib directory
                BJAM_ARGS="stage --stagedir=$PREFIX/$CPU_DIR/$VARIANT"
            elif [ "$ARG" == "clean" ] ; then
                BJAM_ARGS="--clean"
            fi

            ./bjam $BJAM_ARGS \
                --with-date_time \
                --with-filesystem \
                --disable-filesystem2 \
                --with-program_options \
                --with-random \
                --with-regex \
                --with-system \
                --with-thread \
                --with-test \
                --user-config=$CONFIG \
                --layout=system toolset=qcc target-os=qnxnto architecture=$CPU \
                variant=$VARIANT link=shared threading=multi runtime-link=shared \
                optimization=space

            # Move libs from temp dirs to real dirs
            # Need to add "_g" to the name of debug libs because they are installed in 
            # the same dir as the release libs
            if [ "$ARG" == "install" ] ; then
                if [ "$VARIANT" == "debug" ]; then 
                    pushd $PREFIX/$CPU_DIR/$VARIANT/lib
                    PATTERN='\(\S\+\)\(\(\.so\)\.\S\+\)'
                    for FILE in `ls lib* | grep -v _g | grep '\.so\.'` ; do
                        DEBUG_FILE=`echo $FILE | sed -e "s|$PATTERN|\1_g\2|"`
                        SYMLINK=`echo $FILE | sed -e "s|$PATTERN|\1_g\3|"`
                        mv $FILE $DEBUG_FILE
                        ln -s $DEBUG_FILE $SYMLINK
                    done
                    popd
                fi
                DEST_DIR="$PREFIX/$CPU_DIR/usr/lib"
                if [ ! -d $DEST_DIR ] ; then
                    mkdir -p $DEST_DIR
                fi
                mv $PREFIX/$CPU_DIR/$VARIANT/lib/lib* $DEST_DIR
                rm -rf $PREFIX/$CPU_DIR/$VARIANT
            fi
        done
    done
    popd
}

hinstall()
{
    # Copy needed header files to staging dir
    echo "Copying include files"
    for INC_FILE in `cat headers.txt` ; do
        ${QNX_HOST}/usr/bin/qnx_cp -fpc ${BOOST_DIR}/${INC_FILE} ${PREFIX}/usr/include/${INC_FILE}
    done
}

#########################################################
# Begin main script
#########################################################

if [ $# -lt 1 ] ; then
    usage
    exit
fi

ACTION=$1
if [ "$ACTION" != "install" ] && [ "$ACTION" != "hinstall" ] && [ "$ACTION" != "clean" ] ; then
    usage
    exit
fi

BOOST_DIR="`pwd`/.."

PREFIX=`pwd`/boost-stage/target/qnx6
if [ ! -d $PREFIX ] ; then
    mkdir -p $PREFIX
fi

if [ "$ACTION" == "install" ] ; then
    echo "build $ACTION"
    build "$ACTION"
    hinstall
fi

if [ "$ACTION" == "hinstall" ] ; then
    echo "build hinstall"
    hinstall
fi

if [ "$ACTION" == "clean" ] ; then
    echo "build $ACTION"
    build "$ACTION"
fi
