#!/bin/bash

# The set -e option instructs bash to immediately exit 
# if any command [1] has a non-zero exit status. You wouldn't 
# want to set this for your command-line shell, but in a script 
# it's massively helpful. In all widely used general-purpose programming 
# languages, an unhandled runtime error

set +e

cat asd
echo "here1"

set -e

cat asd
echo "here2"

set +e

cat asd
echo "here3"
