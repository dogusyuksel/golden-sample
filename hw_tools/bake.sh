#!/bin/bash
set -euo pipefail

project_name=""
clean_exists="no"
flash_exists="no"
build_exists="no"

if [[ $# -eq 0 ]]; then
    echo "Usage ==> \"./bake.sh <folder_name> [clean] [flash] [build]\""
    exit 1
fi
project_name=$1

if [[ $# -gt 4 ]]; then
    echo "Usage ==> \"./bake.sh <folder_name> [clean] [flash] [build]\""
    exit 1
fi

for var in "$@"
do
    upper_var=${var^^}
    if [[ $upper_var =~ "CLEAN" ]]; then
        clean_exists="yes"
    fi
    if [[ $upper_var =~ "FLASH" ]]; then
        flash_exists="yes"
    fi
    if [[ $upper_var =~ "BUILD" ]]; then
        build_exists="yes"
    fi
done

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
    if [[ $dirname =~ $project_name || "all" == $project_name ]]; then
        if [[ $clean_exists == "yes" ]]; then
            rm -rf  $dirname/build
        fi
        if [[ $build_exists == "yes" ]]; then
            build $dirname
        fi
        if [[ $flash_exists == "yes" ]]; then
            cd  $dirname/build
            st-flash write *.bin 0x08000000
            cd -
        fi

        if [[ "all" != $project_name ]]; then
            exit 0
        fi
    fi
done <<< "$files"

if [[ "all" == $project_name ]]; then
    exit 0
fi

echo "be sure about folder name"

exit 1
