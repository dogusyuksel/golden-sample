#!/bin/bash

set -e

files=$(find . -name '*' -type d -maxdepth 1 -mindepth 1)
while IFS= read -r line; do
    dirname=$(basename "$line")
    cmake $dirname/ -B $dirname/
    make -C $dirname clean
    make -C $dirname all
    cd ..
done <<< "$files"

exit 0
