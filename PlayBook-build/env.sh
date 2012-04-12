#!/bin/bash

DEVSTAGE_DIR=/home/chung/dev/devstage-training/hellolib/devstage

export QNX_HOST=$DEVSTAGE_DIR/host/linux/x86
export QNX_TARGET=$DEVSTAGE_DIR/target/qnx6
export PATH="$QNX_HOST/usr/bin:$PATH"

echo "QNX_HOST=$QNX_HOST"
echo "QNX_TARGET=$QNX_TARGET"

# ensure required BBNDK env variables are set
: ${QNX_HOST:?"Error: QNX_HOST environment variable is not set."}
: ${QNX_TARGET:?"Error: QNX_TARGET environment variable is not set."}
