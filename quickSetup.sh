#!/bin/bash


BASEDIR=$(dirname "$0")

JOBS=2;
if [ "$1" != "" ]; then
  JOBS=$1
fi

mkdir chaiBuild
mkdir bulletBuild
mkdir appBuild
(cd chaiBuild && cmake $BASEDIR/../../ && make -j $JOBS )&&\
(cd bulletBuild && cmake $BASEDIR/../../modules/BULLET/ && make -j $JOBS )&&\
(cd appBuild && cmake $BASEDIR && make -j $JOBS )

echo "Done"
