#!/bin/bash -xe

VERSION=$(grep -oP "(?<=MControlCenter VERSION )[0-9.]*" ../CMakeLists.txt)

DIST_DIR="MControlCenter-$VERSION"
APP_DIR="$DIST_DIR/app"

rm -rf $DIST_DIR
rm -f $DIST_DIR.tar.gz

mkdir $DIST_DIR
mkdir $APP_DIR

cp ../build/mcontrolcenter $APP_DIR
cp ../build/helper/mcontrolcenter-helper $APP_DIR
cp ../src/helper/mcontrolcenter-helper.conf ../src/helper/mcontrolcenter.helper.service $APP_DIR
cp ../resources/mcontrolcenter.desktop ../resources/mcontrolcenter.svg $APP_DIR

cp ./install.sh ./uninstall.sh $DIST_DIR

tar -czvf $DIST_DIR.tar.gz $DIST_DIR

rm -r $DIST_DIR
