#!/bin/bash

git clone https://github.com/OpenCyphal/libcanard.git libcanard
cd libcanard
git checkout 43de1c4966b8d1e5d57978949d63e697f045b358

git submodule update --init --recursive

cd ..

cmake .
make
