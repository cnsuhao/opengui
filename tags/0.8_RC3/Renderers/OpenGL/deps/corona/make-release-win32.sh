#!/bin/sh

die() {
    echo "Error, aborting..."
    exit 1
}

vc6die() {
    echo "Error building corona.dsw"
    echo "See build log: vc6-build.log"
    exit 1
}

vc7die() {
    echo "Error building corona.sln"
    echo "See build log: vc7-build-release.log or vc7-build-debug.log"
    exit 1
}

echo
echo "Building Corona VC6 workspace..."

msdev vc6/corona.dsw /MAKE ALL /OUT vc6-build.log || vc6die

echo
echo "Building Corona VC7 solution..."

devenv vc7/corona.sln /build Release /out vc7-build-release.log || vc7die
devenv vc7/corona.sln /build Debug   /out vc7-build-debug.log   || vc7die

echo
echo "Build complete.  Packaging..."
echo

DIST=dist
NAME=corona-1.0.2-vc6

scons -f vc6/dist.py prefix=$DIST/$NAME || die
find . -name .sconsign | xargs rm -f

rm -f $DIST/$NAME.zip
(cd $DIST && zip -r $NAME.zip $NAME) || die


NAME=corona-1.0.2-vc7

scons -f vc7/dist.py prefix=$DIST/$NAME || die
find . -name .sconsign | xargs rm -f

rm -f $DIST/$NAME.zip
(cd $DIST && zip -r $NAME.zip $NAME) || die

echo
echo "Win32 release completed."
