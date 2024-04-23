#!/bin/bash

files=$(find . -name '*' -type d -maxdepth 1 -mindepth 1)
while IFS= read -r line; do
    dirname=$(basename "$line")
    rm -rf  $dirname/build
done <<< "$files"

exit 0
