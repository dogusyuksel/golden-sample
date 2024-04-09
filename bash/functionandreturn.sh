#!/bin/bash

my_fun() {
    # returns 0 if the first arguments is "a"
    # 1 otherwise
    if [ "${1}" = "a" ]
    then
        return 1
    fi

    return 0
}

my_fun "a"
echo "a=$?"
my_fun "b"
echo "b=$?"

