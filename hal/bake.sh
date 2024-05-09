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
    mkdir  base_example/build
    cmake base_example/ -B base_example/build/
    make -C base_example/build clean
    make -C base_example/build all
    arm-none-eabi-objcopy -O binary base_example/build/base_example.elf base_example/build/base_example.bin
}

files=$(find . -name '*' -type d -maxdepth 1 -mindepth 1)
while IFS= read -r line; do
    dirname=$(basename "$line")
    if [[ $dirname != "base_example" && $dirname != "assets" ]]; then
        if [[ $dirname =~ $project_name || "all" == $project_name ]]; then
            if [[ $clean_exists == "yes" ]]; then
                rm -rf  base_example/build
                rm -rf  $dirname/$dirname.bin
            fi
            if [[ $build_exists == "yes" ]]; then
                cd .. && git apply hal/$dirname/$dirname.patch && cd -
                build
                cd ../ && git apply -R hal/$dirname/$dirname.patch && cd -
            fi
            if [[ $flash_exists == "yes" ]]; then
                cd  base_example/build
                cp -rf *.bin ../../$dirname/$dirname.bin
                cd ../../$dirname
                st-flash write *.bin 0x08000000
                cd ../
            fi

            if [[ "all" != $project_name ]]; then
                exit 0
            fi
        fi
    fi
done <<< "$files"

if [[ "all" == $project_name ]]; then
    exit 0
fi

echo "be sure about folder name"

exit 1
