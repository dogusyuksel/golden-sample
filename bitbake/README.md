
This folder contains very basic c project thats build and test steps are handled by bitbake tool.

How to setup the bitbake environment can be found in the docker/Dockerfile

This is kind of small example but multiple layer usage, multiple class usage and multiple recipe usages can be found.

Some comamnds I found useful are:

* bitbake -s
* bitbake-layers show-layers
* bitbake-layers show-recipes
* bitbake world
* bitbake <recipename>
* bitbake <recipename>:<functionname>
* bitbake -g <recipename> // to create dependency file
* bitbake -e > <filename> // give idea about environment
