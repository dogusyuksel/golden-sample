#!/bin/bash

status=$(git status)

if [[ $status == *"working tree clean"* ]]; then
    exit 0
fi

echo ">>>>>>>>>>>>>>>>>>>>>>>> tree is dirty <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"
echo "$status"

exit 1
