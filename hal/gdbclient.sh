#!/bin/bash

if [ "$#" -ne 1 ]; then
        echo "type folder name"
        exit 1
fi

gdb-multiarch $1/build/$1.elf

# then type
# target extended-remote localhost:3333
# 3333 can be found netstat -tunlpa | grep openocd

exit 0
