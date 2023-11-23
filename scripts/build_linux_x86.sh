#!/usr/bin/bash
rm -rf build && mkdir build && cd build

cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_TEST=ON -DCMAKE_INSTALL_PREFIX=simple.cv -DBUILD_USE_STB=ON -DBUILD_LOG=ON ..
make   && make install
# ./bin/test_base