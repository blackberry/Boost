#!/bin/bash

# ensure required BBNDK env variables are set
: ${QNX_HOST:?"Error: QNX_HOST environment variable is not set."}
: ${QNX_TARGET:?"Error: QNX_TARGET environment variable is not set."}

pushd ..
BOOST_DIR=`pwd`
popd

PREFIX=`pwd`/boost-install
if [ ! -d $PREFIX ] ; then
    mkdir -p $PREFIX
fi

pushd $BOOST_DIR

if [ ! -f ./bjam ] ; then
    ./bootstrap.sh
fi

# Build and install all
PYTHON_SRC_DIR=/home/chung/dev/product-rim/trunk/tools/python-3.2
./bjam install -q include=$PYTHON_SRC_DIR:$PYTHON_SRC_DIR/Include \
    --prefix=$PREFIX \
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
    --with-python \
    --with-random \
    --with-regex \
    --with-serialization \
    --with-signals \
    --with-system \
    --with-test \
    --with-thread \
    --with-timer \
    --with-wave \
    --user-config=blackberry-armv7le-config.jam \
    --layout=system toolset=qcc target-os=qnxnto

popd

