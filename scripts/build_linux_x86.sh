#!/usr/bin/bash
rm -rf build && mkdir build && cd build

cmake -DCMAKE_BUILD_TYPE=Release ..
make -j4 && make install
# ./bin/test_base