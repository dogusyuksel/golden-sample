#!/bin/bash

if [ ! -d "CANBUS/libcanard" ]; then
    git clone https://github.com/OpenCyphal/libcanard.git CANBUS/libcanard
    cd CANBUS/libcanard
    git checkout 43de1c4966b8d1e5d57978949d63e697f045b358
    git submodule update --init --recursive
    cd -
    patch -d CANBUS -p1 < ./CANBUS/transport.py.patch
    patch -d CANBUS -p1 < ./CANBUS/canard_stm32.patch
    ./CANBUS/libcanard/dsdl_compiler/libcanard_dsdlc ./CANBUS/nodes --incdir ./CANBUS/libcanard/dsdl_compiler/pyuavcan/uavcan --outdir ./CANBUS/generated_files
fi


exit 0
