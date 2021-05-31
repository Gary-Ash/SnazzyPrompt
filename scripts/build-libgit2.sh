#!/usr/bin/env bash
#*****************************************************************************************
# build-libgit2.sh
#
# Build libgit2 as a static library
#
# Author   :  Gary Ash <gary.ash@icloud.com>
# Created  :  12-Jan-2020  1:22pm
# Modified :  12-Jan-2020  1:22pm
#
# Copyright © 2020 By Gee Dbl A All rights reserved.
#*****************************************************************************************
set -e
cd ..
git clone --recurse-submodules --single-branch https://github.com/libgit2/libgit2.git
export PKG_CONFIG_PATH=/usr/local/opt/openssl/lib/pkgconfig
cd libgit2
mkdir build
cd build

cmake -DBUILD_SHARED_LIBS:BOOL=OFF \
	-DUSE_ICONV:BOOL=OFF \
    -DLIBSSH2_INCLUDE_DIRS:PATH=/usr/local/include/ \
    -DUSE_BUNDLED_ZLIB:BOOL=ON \
    -DBUILD_CLAR:BOOL=OFF \
    -DTHREADSAFE:BOOL=ON \
    ..
cmake --build .
