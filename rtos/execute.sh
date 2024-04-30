#!/bin/bash

if [[ $# -ne 1 ]]; then
    echo "type project name"
    exit 1
fi

build() {
    mkdir  $1/build
    cmake $1/ -B $1/build/
    make -C $1/build clean
    make -C $1/build all
    arm-none-eabi-objcopy -O binary $1/build/$1.elf $1/build/$1.bin
}

files=$(find . -name '*' -type d -maxdepth 1 -mindepth 1)
while IFS= read -r line; do
    dirname=$(basename "$line")
    if [[ $dirname =~ $1 ]]; then
        rm -rf  $dirname/build
        build $dirname
        cd  $dirname/build
        st-flash write *.bin 0x08000000
        cd ../..

        exit 0
    fi
done <<< "$files"

exit 1
