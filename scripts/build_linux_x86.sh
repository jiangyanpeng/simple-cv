#!/usr/bin/bash
rm -rf build && mkdir build && cd build

cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_TEST=ON -DCMAKE_INSTALL_PREFIX=simple.cv ..
make -j4 && make install
# ./bin/test_base