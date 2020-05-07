#!/bin/bash
set -e

SOURCE_DIR=`pwd`

if [ -n "$1" ]; then
    VERSION=`git describe --tags`
    if [ -z "$VERSION" ]; then
        VERSION=` git rev-parse HEAD`
    fi
    
    echo "Current verion: $VERSION, The version to will be set: $1"
    echo "Please check the follow list:"
    echo "    - Test is ok ?"
    echo "    - Translation is ok ?"
    echo "    - Setup file is ok ?"
    echo "    - Update_*.xml is ok ?"
    
    read -t 30 -p "Be sure to input Y, not input N: " INPUT
    if [ "$INPUT" != "Y" -a "$INPUT" != "y" ]; then
        exit 0
    fi
    git tag -a $1 -m "Release $1"
fi

VERSION=`git describe --tags`
if [ -z "$VERSION" ]; then
    VERSION=`git rev-parse --short HEAD`
fi

sed -i "s/^\!define PRODUCT_VERSION.*/\!define PRODUCT_VERSION \"${VERSION}\"/g" ${SOURCE_DIR}/Install/Install.nsi
sed -i "s/^\SET(BUILD_VERSION.*/\SET(BUILD_VERSION \"${VERSION}\")/g" ${SOURCE_DIR}/CMakeLists.txt
sed -i "s/^version: '.*{build}'/version: '${VERSION}.{build}'/g" ${SOURCE_DIR}/appveyor.yml
sed -i "s/BUILD_VERSION:.*/BUILD_VERSION: \"${VERSION}\"/g" ${SOURCE_DIR}/appveyor.yml

DEBIAN_VERSION=`echo ${VERSION}|cut -d "v" -f 2`
sed -i "s/[0-9]\+\.[0-9]\+\.[0-9]\+/${DEBIAN_VERSION}/g" ${SOURCE_DIR}/README*.md

if [ -n "$1" ]; then
    git add .
    git commit -m "Release $1"
    git push
    git tag -d $1
    git tag -a $1 -m "Release $1"
    git push origin :refs/tags/$1
    git push origin $1
fi
