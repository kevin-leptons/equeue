#!/bin/bash

# NAME
#
#   ctl - Control project's building
#
# SYNOPSIS
#
#   ctl build   build this project
#   ctl clear   clear build files
# 
# AUTHORS
#
#   Kevin Leptons <kevin.leptons@gmail.com>

# bash options
set -e

ROOT=$(realpath .)
SRC="$ROOT/src"
DEST="$ROOT/dest"
DEST_MAN="$DEST/man/equeue.3.gz"
DIST="$ROOT/dist"
DIST_PKG="$DIST/equeue"
VERSION="0.3.0"

# help menu
HELP="USAGE\n
    $(basename $0) build        build repo
    $(basename $0) clear        clear build files
    $(basename $0) dist         pack repo into .deb file
    $(basename $0) -h           show help menu\n"

ctl_build()
{
    # prepare
    mkdir -vp $DEST
    cd $DEST

    # use cmake, make to build
    cmake ..
    make

    # man page
    mkdir -vp $(dirname $DEST_MAN)
    cp $ROOT/equeue.3.man $DEST_MAN
    sed -i "s/\$BUILD_DATE/$(date)/g" $DEST_MAN
    sed -i "s/\$VERSION/$VERSION/g" $DEST_MAN
}

ctl_dist()
{
    if [ ! -d $DEST ]; then
        echo "Use 'ctl build' before 'ctl dist'"
        exit 1
    fi
    rm -rf $DIST 
    mkdir -vp $DIST_PKG
    cp -r debian $DIST_PKG/DEBIAN
    sed -i "s/\$VERSION/$VERSION/g" $DIST_PKG/DEBIAN/control

    cd $DEST
    make install DESTDIR=$DIST_PKG

    mkdir -vp $DIST_PKG/usr/share/man/man3
    cp $DEST_MAN $DIST_PKG/usr/share/man/man3

    local DIST_DOC_EX="$DIST_PKG/usr/share/doc/equeue/example"
    mkdir -vp $DIST_DOC_EX
    cp $SRC/imp/endpoint-test.c $DIST_DOC_EX/simple.c

    cd $DIST
    dpkg-deb --build -D $DIST_PKG $DIST
}

ctl_clear()
{
    rm -rf $DEST $DIST
    rm -rf cmake-build-debug
    if [ -f core ]; then
        rm core
    fi
}

ctl_help()
{
    printf "$HELP"
}

# parse arguments
case "$1" in
    build) ctl_build; exit 0;;
    dist) ctl_dist; exit 0;;
    clear) ctl_clear; exit 0;;
    -h) ctl_help; exit 0;;
    *) ctl_help; exit 1;;
esac
