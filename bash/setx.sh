#!/bin/bash

# Enables a mode of the shell where all executed commands 
# are printed to the terminal. In your case it's clearly 
# used for debugging, which is a typical use case for set -x : 
# printing every command as it is executed may help you to visualize 
# the control flow of the script if it is not functioning as expected.

set +x

echo "asd"
echo "bsd"

set -x

echo "asd"
echo "bsd"

