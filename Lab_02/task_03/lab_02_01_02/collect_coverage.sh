#!/bin/bash

set -e

if [ -f test.info ]; then
    rm test.info
fi

./build_debug.sh
./build_debug_asan.sh
./build_debug_msan.sh
./build_debug_ubsan.sh

cd func_tests/scripts/
./func_tests.sh
cd ../../

lcov -t "Test Coverage" -o test.info -c -d .
genhtml -o report test.info