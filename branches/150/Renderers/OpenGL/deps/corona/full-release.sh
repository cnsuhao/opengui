#!/bin/sh

die() {
    echo
    echo "Error, aborting..."
    exit 1
}


BASE=corona-1.0.2


export CVSROOT=`cat CVS/Root`
echo
echo "Using CVSROOT: $CVSROOT"
echo

# enter 'release' directory
mkdir -p release || die
cd release || die

# $FILES is where all of the files to be uploaded go
FILES=files
mkdir -p $FILES || die

# check out the base CVS repository
rm -rf corona || die
cvs export -D now corona || die
cp -r corona corona-unix || die
cp -r corona corona-doxygen || die

echo
echo "Building binary release..."
case `uname` in
    CYGWIN*)
        echo "Platform: Win32"
        cp -r corona corona-win32 || die
        (cd corona-win32 && ./make-release-win32.sh) || die
        cp corona-win32/dist/$BASE-vc6.zip "$FILES" || die
        cp corona-win32/dist/$BASE-vc7.zip "$FILES" || die
        ;;

    *)
        echo "WARNING: Unknown platform, not building binary release"
        ;;
esac

echo
echo "Building UNIX release..."
echo

(cd corona-unix && ./bootstrap && ./configure && make dist) || die
cp corona-unix/$BASE.tar.gz "$FILES" || die

echo
echo "Building Doxygen release..."
echo

(cd corona-doxygen/doc/doxygen && ./doxygen-dist.sh) || die
cp corona-doxygen/doc/doxygen/$BASE-doxygen.chm     "$FILES" || die
cp corona-doxygen/doc/doxygen/$BASE-doxygen.zip     "$FILES" || die
cp corona-doxygen/doc/doxygen/$BASE-doxygen.tar.bz2 "$FILES" || die

echo
echo "Building source release..."
echo

tar cfvj "$FILES/$BASE-src.tar.bz2" corona
