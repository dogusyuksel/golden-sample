#!/bin/bash

set -e

files=$(find . -name '*' -type d -maxdepth 1 -mindepth 1)
while IFS= read -r line; do
    dirname=$(basename "$line")
    mkdir  $dirname/build
    cmake $dirname/ -B $dirname/build/
    make -C $dirname/build clean
    make -C $dirname/build all
    cd ..
done <<< "$files"

exit 0
