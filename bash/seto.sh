#!/bin/bash

# This setting prevents errors in a pipeline from being masked. 
# If any command in a pipeline fails, that return code will be 
# used as the return code of the whole pipeline. By default, 
# the pipeline's return code is that of the last command even if it succeeds. 
# Imagine finding a sorted list of matching lines in a file:

set +o pipefail

grep asd not_existent_file | sort

echo "$?"


set -o pipefail

grep asd not_existent_file | sort

echo "$?"

