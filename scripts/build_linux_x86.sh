#!/usr/bin/bash
rm -rf build && mkdir build && cd build

cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_TEST=ON -DCMAKE_INSTALL_PREFIX=simple.cv -DBUILD_USE_STB=ON ..
make -j4 && make install
# ./bin/test_base