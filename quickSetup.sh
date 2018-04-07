#!/bin/bash

BASE=$(readlink -f "$0")
BASEDIR=$(dirname "$BASE")
echo "BASEDIR: " $BASEDIR
JOBS=2;
if [ "$1" != "" ]; then
  JOBS=$1
fi

ARGS=" -DCMAKE_BUILD_TYPE=RELWITHDEBINFO "

mkdir chaiBuild
mkdir bulletBuild
mkdir appBuild
(cd chaiBuild && cmake $ARGS $BASEDIR/../../ && make -j $JOBS )&&\
(cd bulletBuild && cmake $ARGS $BASEDIR/../../modules/BULLET/ && make -j $JOBS )&&\
(cd appBuild && cmake $ARGS $BASEDIR && make -j $JOBS )

echo "Done"
