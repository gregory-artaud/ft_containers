#!/bin/bash

LOGS_DIRECTORY=logs

rm -rf $LOGS_DIRECTORY
mkdir -p $LOGS_DIRECTORY

FAIL=0

./stl > $LOGS_DIRECTORY/stl.log 2>&1 || FAIL=1
./ft > $LOGS_DIRECTORY/ft.log 2>&1 || FAIL=1

diff $LOGS_DIRECTORY/stl.log $LOGS_DIRECTORY/ft.log > $LOGS_DIRECTORY/diff.log && rm $LOGS_DIRECTORY/diff.log
DIFF=$?

if [[ $FAIL -ne 0 || $DIFF -ne 0 ]]
then
	exit 1
fi
