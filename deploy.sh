#!/bin/bash
set -e

SOURCE_DIR=`pwd`

PRE_TAG=`git tag --sort=-creatordate | head -n 1`

if [ -n "$1" ]; then
    VERSION=`git describe --tags`
    if [ -z "$VERSION" ]; then
        VERSION=`git rev-parse HEAD`
    fi

    if [ -n "$2" ]; then
        MESSAGE="Release $1 $2"
    else
        MESSAGE="Release $1"
    fi

    PRE_TAG=`git tag --sort=-taggerdate | head -n 1`
    echo "Current version: $VERSION, current tag: $PRE_TAG. The version to will be set tag version: $1 message: $MESSAGE"
    echo "Please check the follow list:"
    echo "    - Test is ok ?"
    echo "    - Translation is ok ?"
    echo "    - Setup file is ok ?"
    echo "    - Update_*.xml is ok ?"
    
    read -t 30 -p "Be sure to input Y, not input N: " INPUT
    if [ "$INPUT" != "Y" -a "$INPUT" != "y" ]; then
        exit 0
    fi
    git tag -a $1 -m "Release $1 ${MESSAGE}"
else
    echo "Usage: $0 release_version [release_message]"
    echo "   release_version format: [v][0-9].[0-9].[0-9]"
    exit -1
fi

VERSION=`git describe --tags`
if [ -z "$VERSION" ]; then
    VERSION=`git rev-parse --short HEAD`
fi

sed -i "s/^\!define PRODUCT_VERSION.*/\!define PRODUCT_VERSION \"${VERSION}\"/g" ${SOURCE_DIR}/Install/Install.nsi
sed -i "s/^\SET(ChineseChessControl_VERSION.*/SET(ChineseChessControl_VERSION \"${VERSION}\")/g" ${SOURCE_DIR}/CMakeLists.txt
sed -i "s/    SET(${PROJECT_NAME}_VERSION.*/    SET(${PROJECT_NAME}_VERSION \"${VERSION}\")/g" ${SOURCE_DIR}/Src/CMakeLists.txt
sed -i "s/^version: '.*{build}'/version: '${VERSION}.{build}'/g" ${SOURCE_DIR}/appveyor.yml
sed -i "s/ChineseChessControl_VERSION:.*/ChineseChessControl_VERSION: \"${VERSION}\"/g" ${SOURCE_DIR}/appveyor.yml
sed -i "s/ChineseChessControl_VERSION:.*/ChineseChessControl_VERSION: \"${VERSION}\"/g" ${SOURCE_DIR}/.github/workflows/msvc.yml
sed -i "s/ChineseChessControl_VERSION:.*/ChineseChessControl_VERSION: \"${VERSION}\"/g" ${SOURCE_DIR}/.github/workflows/mingw.yml
sed -i "s/ChineseChessControl_VERSION:.*/ChineseChessControl_VERSION: \"${VERSION}\"/g" ${SOURCE_DIR}/.github/workflows/android.yml
sed -i "s/ChineseChessControl_VERSION:.*/ChineseChessControl_VERSION: \"${VERSION}\"/g" ${SOURCE_DIR}/.github/workflows/build.yml
sed -i "s/ChineseChessControl_VERSION:.*/ChineseChessControl_VERSION: \"${VERSION}\"/g" ${SOURCE_DIR}/.github/workflows/doxygen.yml
sed -i "s/export VERSION=.*/export VERSION=\"${VERSION}\"/g" ${SOURCE_DIR}/.travis.yml
sed -i "s/v[0-9]\+\.[0-9]\+\.[0-9]\+/${VERSION}/g" ${SOURCE_DIR}/README*.md

DEBIAN_VERSION=`echo ${VERSION}|cut -d "v" -f 2`
sed -i "s/chinesechess (.*)/chinesechess (${DEBIAN_VERSION})/g" ${SOURCE_DIR}/debian/changelog
sed -i "s/Version=.*/Version=${DEBIAN_VERSION}/g" ${SOURCE_DIR}/Package/share/applications/org.Rabbit.ChineseChess.desktop
#sed -i "s/[0-9]\+\.[0-9]\+\.[0-9]\+/${DEBIAN_VERSION}/g" ${SOURCE_DIR}/README*.md
sed -i "s/[0-9]\+\.[0-9]\+\.[0-9]\+/${DEBIAN_VERSION}/g" ${SOURCE_DIR}/App/Qt/ChineseChess/android/AndroidManifest.xml
sed -i "s/ChineseChessControl_VERSION:.*/ChineseChessControl_VERSION: \"${DEBIAN_VERSION}\"/g" ${SOURCE_DIR}/.github/workflows/macos.yml
sed -i "s/ChineseChessControl_VERSION:.*/ChineseChessControl_VERSION: \"${DEBIAN_VERSION}\"/g" ${SOURCE_DIR}/.github/workflows/ubuntu.yml
if [ -f ${SOURCE_DIR}/vcpkg.json ]; then
    sed -i "s/\"version-string\":[0-9]\+\.[0-9]\+\.[0-9]\+\".*\"/\"version-string\":\"${DEBIAN_VERSION}\"/g" ${SOURCE_DIR}/vcpkg.json
fi

MAJOR_VERSION=`echo ${DEBIAN_VERSION}|cut -d "." -f 1`
sed -i "s/android:versionCode=.*android/android:versionCode=\"${MAJOR_VERSION}\" android/g" ${SOURCE_DIR}/App/Qt/ChineseChess/android/AndroidManifest.xml

MSVC_VERSION="`echo ${DEBIAN_VERSION} | sed "s/\./,/g"`,0"

sed -i "s/FILEVERSION \+[0-9]*,[0-9]*,[0-9]*,[0-9]*/FILEVERSION ${MSVC_VERSION}/g" ${SOURCE_DIR}/UI/MFC/ChineseChessView.rc
sed -i "s/PRODUCTVERSION \+[0-9]*,[0-9]*,[0-9]*,[0-9]*/FILEVERSION ${MSVC_VERSION}/g" ${SOURCE_DIR}/UI/MFC/ChineseChessView.rc
sed -i "s/VALUE \"FileVersion\", *\"[0-9]*, *[0-9]*, *[0-9]*, *[0-9]*\"/VALUE \"FileVersion\", \"${MSVC_VERSION}\"/g" ${SOURCE_DIR}/UI/MFC/ChineseChessView.rc
sed -i "s/VALUE \"ProductVersion\", *\"[0-9]*, *[0-9]*, *[0-9]*, *[0-9]*\"/VALUE \"ProductVersion\", \"${MSVC_VERSION}\"/g" ${SOURCE_DIR}/UI/MFC/ChineseChessView.rc
sed -i "s/[0-9]\+\.[0-9]\+\.[0-9]\+/${DEBIAN_VERSION}/g" ${SOURCE_DIR}/UI/MFC/ChineseChessView.rc

sed -i "s/FILEVERSION \+[0-9]*,[0-9]*,[0-9]*,[0-9]*/FILEVERSION ${MSVC_VERSION}/g" ${SOURCE_DIR}/UI/ActiveX/ChineseChessActiveX.rc
sed -i "s/PRODUCTVERSION \+[0-9]*,[0-9]*,[0-9]*,[0-9]*/FILEVERSION ${MSVC_VERSION}/g" ${SOURCE_DIR}/UI/ActiveX/ChineseChessActiveX.rc
sed -i "s/VALUE \"FileVersion\", *\"[0-9]*, *[0-9]*, *[0-9]*, *[0-9]*\"/VALUE \"FileVersion\", \"${MSVC_VERSION}\"/g" ${SOURCE_DIR}/UI/ActiveX/ChineseChessActiveX.rc
sed -i "s/VALUE \"ProductVersion\", *\"[0-9]*, *[0-9]*, *[0-9]*, *[0-9]*\"/VALUE \"ProductVersion\", \"${MSVC_VERSION}\"/g" ${SOURCE_DIR}/UI/ActiveX/ChineseChessActiveX.rc
sed -i "s/[0-9]\+\.[0-9]\+\.[0-9]\+/${DEBIAN_VERSION}/g" ${SOURCE_DIR}/UI/ActiveX/ChineseChessActiveX.rc

sed -i "s/\"ChineseChessActiveX.[0-9]\+\.[0-9]\+\.[0-9]\+\"/\"ChineseChessActiveX.${DEBIAN_VERSION}\"/g" ${SOURCE_DIR}/UI/ActiveX/ChineseChessActiveXCtrl.cpp
sed -i "s/\"ChineseChessActiveXPropPage.[0-9]\+\.[0-9]\+\.[0-9]\+\"/\"ChineseChessActiveXPropPage.${DEBIAN_VERSION}\"/g" ${SOURCE_DIR}/UI/ActiveX/ChineseChessActiveXPropPage.cpp

sed -i "s/FILEVERSION \+[0-9]*,[0-9]*,[0-9]*,[0-9]*/FILEVERSION ${MSVC_VERSION}/g" ${SOURCE_DIR}/App/MFC/ChineseChessMFC/ChineseChessMFC.rc
sed -i "s/PRODUCTVERSION \+[0-9]*,[0-9]*,[0-9]*,[0-9]*/FILEVERSION ${MSVC_VERSION}/g" ${SOURCE_DIR}/App/MFC/ChineseChessMFC/ChineseChessMFC.rc
sed -i "s/VALUE \"FileVersion\",.*/VALUE \"FileVersion\", \"${MSVC_VERSION}\"/g" ${SOURCE_DIR}/App/MFC/ChineseChessMFC/ChineseChessMFC.rc
sed -i "s/VALUE \"ProductVersion\",.*/VALUE \"ProductVersion\", \"${MSVC_VERSION}\"/g" ${SOURCE_DIR}/App/MFC/ChineseChessMFC/ChineseChessMFC.rc
sed -i "s/[0-9]\+\.[0-9]\+\.[0-9]\+/${DEBIAN_VERSION}/g" ${SOURCE_DIR}/App/MFC/ChineseChessMFC/ChineseChessMFC.rc

CHANGLOG_TMP=${SOURCE_DIR}/debian/changelog.tmp
CHANGLOG_FILE=${SOURCE_DIR}/debian/changelog
echo "rabbitcommon (${DEBIAN_VERSION}) unstable; urgency=medium" > ${CHANGLOG_FILE}
echo "" >> ${CHANGLOG_FILE}
echo "`git log --pretty=format:'    * %s' ${PRE_TAG}..HEAD`" >> ${CHANGLOG_FILE}
echo "" >> ${CHANGLOG_FILE}
echo " -- `git log --pretty=format:'%an <%ae>' HEAD^..HEAD`  `date --rfc-email`" >> ${CHANGLOG_FILE}

if [ -n "$1" ]; then
    git add .
    git commit -m "Release $1"
    git push
    git tag -d $1
    git tag -a $1 -m "Release $1"
    git push origin :refs/tags/$1
    git push origin $1
fi
