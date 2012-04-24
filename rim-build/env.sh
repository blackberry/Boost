#!/bin/bash

# NOTE: To use the script, you have to "source" it into your shell

# Get absolute path of script
SCRIPT_PATH=$PWD/$BASH_SOURCE
SCRIPT_DIR=`dirname $SCRIPT_PATH`

# Download project dependencies
mvn -s dev-settings.xml validate

# Set environment variables for QNX toolchain
export QNX_TARGET="$SCRIPT_DIR/devstage/target/qnx6"
export QNX_HOST="$SCRIPT_DIR/devstage/host/linux/x86"
export PATH="$QNX_HOST/usr/bin:$PATH"
export MAKEFLAGS="-I$QNX_TARGET/usr/include -I$QNX_TARGET/usr/include/mk"

echo "QNX_HOST=$QNX_HOST"
echo "QNX_TARGET=$QNX_TARGET"
