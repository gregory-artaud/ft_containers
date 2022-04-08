#!/bin/bash

LOGS_DIRECTORY=logs

mkdir -p $LOGS_DIRECTORY

./vector > $LOGS_DIRECTORY/vector.log || exit 1
./map > $LOGS_DIRECTORY/map.log || exit 1
./stack > $LOGS_DIRECTORY/stack.log || exit 1
