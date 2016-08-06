#!/bin/sh
BASEDIR=`dirname $0`
mkdir -p $BASEDIR/Project
pushd $BASEDIR/Project >/dev/null
cmake -GXcode ..
popd >/dev/null

