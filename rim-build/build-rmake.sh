#!/bin/bash

# Script to wrap the make command that is run on the recursive makefiles

# ensure required BBNDK env variables are set
: ${QNX_HOST:?"Error: QNX_HOST environment variable is not set."}
: ${QNX_TARGET:?"Error: QNX_TARGET environment variable is not set."}

# Get absolute path of script
SCRIPT_PATH=$PWD/$BASH_SOURCE
SCRIPT_DIR=`dirname $SCRIPT_PATH`

pushd $SCRIPT_DIR

usage()
{
    cat << EOF
Usage: $0 [OPTION]

Options:

  -h                Display a short help message and exit
  -t BUILD_TYPE     Type of build: <install | hinstall | clean> 
  -c CPU            CPU: <arm | x86> (will build both if not specified)
  -d                Build debug binaries only (both release and debug are built if not specified)
EOF
}

error_and_exit () {
    if test -n "$1"; then
        echo $1 >&2
    fi
    echo >&2
    echo "Try \`"$basename" -h' for more information." >&2
    exit
}

parse_script_option_list () {
    set +e
    options=`getopt ht:c:d $@`
    if test ! $? -eq 0; then
        error_and_exit
    fi
    set -e

    eval set -- $options
    while [ $# -gt 0 ]; do
        case "$1" in
            -h) shift; usage; exit;;
            -t) shift; BUILD_TYPE=$1; 
                if [ "$BUILD_TYPE" != "install" ] && [ "$BUILD_TYPE" != "hinstall" ] && [ "$BUILD_TYPE" != "clean" ] ; then
                    error_and_exit "Invalid BUILD_TYPE: $BUILD_TYPE"
                fi
                shift;;
            -c) shift; CPU=$1; 
                if [ "$CPU" != "arm" ] && [ "$CPU" != "x86" ] ; then
                    error_and_exit "Invalid CPU: $CPU"
                fi
                shift;;
            -d) shift; DEBUG_BUILD=true;;
            --) shift; break;;
            *) error_and_exit "Unknown option: $1" >&2;;
        esac
    done

    if [ $# -gt 0 ] ; then
        error_and_exit "Unknown args: $@"
    fi
}

build()
{
    pushd $SCRIPT_DIR/..

    if [ "$CPU" == "" ] ; then
        CPU_OPT=""
    else
        CPU_OPT="CPULIST=$CPU"
    fi

    if [ "$DEBUG_BUILD" == "true" ] ; then
        DEBUG_OPT='VARIANTLIST=g' 
    fi

    if [ "$BUILD_TYPE" == "install" ] || [ "$BUILD_TYPE" == "hinstall" ] ; then
        PREFIX_OPT="INSTALL_ROOT_nto=$PREFIX"
    fi

    make -j 4 $BUILD_TYPE $CPU_OPT $DEBUG_OPT $PREFIX_OPT

    popd
}

#########################################################
# Begin main script
#########################################################
parse_script_option_list "$@"
PREFIX=`dirname $SCRIPT_DIR`/boost-stage
build
