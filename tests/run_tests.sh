#!/bin/bash

LOGS_DIRECTORY=logs

mkdir -p $LOGS_DIRECTORY

./stl > $LOGS_DIRECTORY/stl.log 2>&1 || exit 1
./ft > $LOGS_DIRECTORY/ft.log 2>&1 || exit 1

diff $LOGS_DIRECTORY/stl.log $LOGS_DIRECTORY/ft.log > $LOGS_DIRECTORY/diff.log && rm $LOGS_DIRECTORY/diff.log
