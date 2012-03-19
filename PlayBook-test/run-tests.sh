#!/bin/sh

# Run every library's test programs

TEST_DIR=`pwd`
BOOST_DIR=`pwd`/..

cd $BOOST_DIR
for EXE_PATH in `cat $TEST_DIR/exe.list | grep -v '#'` ; do
    LIB_DIR=`echo $EXE_PATH | sed -e 's|^bin.v2\/\(libs\/.\+\/test\)\/.\+$|\1|'`
    if [ -d $LIB_DIR ] ; then
        cd $LIB_DIR
    else
        echo "LIB_DIR ($LIB_DIR) not found for $EXE_PATH"
        continue
    fi 
    EXE_CMD="../../../$EXE_PATH"
    echo "Running $EXE_CMD"
    ./$EXE_CMD
    RET=$?
    echo "$EXE_CMD returned $RET"
    cd $BOOST_DIR
done
cd $TEST_DIR
