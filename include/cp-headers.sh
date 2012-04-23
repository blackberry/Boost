#!/bin/sh

usage()
{
    echo "$0 <STAGE_DIR>"
}

if [ $# -lt 1 ] ; then
    usage
    exit
fi

#STAGE_DIR=$INSTALL_ROOT_nto
#STAGE_DIR=$QNX_TARGET
#STAGE_DIR=/tmp/target
STAGE_DIR=$1

BOOST_DIR="`pwd`/.."
for INC_FILE in `cat headers.txt` ; do
    ${QNX_HOST}/usr/bin/qnx_cp -fpc ${BOOST_DIR}/${INC_FILE} ${STAGE_DIR}/usr/include/${INC_FILE}
done
