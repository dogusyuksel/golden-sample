#!/bin/bash

set -e

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

    if [[ $# -eq 1 ]]; then
        if [[ $dirname =~ $1 ]]; then
            build $dirname
            exit 0
        fi
    fi

    if [[ $# -eq 0 ]]; then
        build $dirname
    fi
done <<< "$files"

if [[ $# -eq 1 ]]; then
    echo "be careful about the argument syntax"
    exit 1
fi

exit 0
