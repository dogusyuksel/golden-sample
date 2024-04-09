#!/bin/bash

# Affects variables. When set, a reference to any variable you haven't 
# previously defined - with the exceptions of $* and $@ - is an error, and 
# causes the program to immediately exit. Languages like Python, C, 
# Java and more all behave the same way, for all sorts of good reasons. 
# One is so typos don't create new variables without you realizing it.

set +u

firstName="Aaron"
fullName="$firstname Maxwell"
echo "$fullName"

set -u

firstName="Aaron"
fullName="$firstname Maxwell"
echo "$fullName"

