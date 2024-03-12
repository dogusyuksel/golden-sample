# cicd-example

This is a dummy C project that was just created for using CI tools.

The actual source code with "main" function is located under ReadPeriodic/src

HWIO folder is considered like it is actually a hardware driver library that cannot be used/executed withot the actual hardware (to use CMock in Ceedling unit tests) and TMR folder is considered some third party library that is used by the actual application.

So this project's actual purpose is to learn and implement the below things;

1. make
```
check "Makefile".
It is really basic one but shows the basis of how to compile source codes located in different folder paths to build one executable
```

2. clang usage
```
check scripts/format_check.sh
```

3. splint usage
```
check scripts/lint_check.sh
```

4. github api usage to check working tree is clean
```
check scripts/dirty_check.sh
```

5. Unity Ceedling Unit Testing usage with CMock
```
check scripts/run_unittests.sh
        ○ goto parent folder of the project
        ○ type "ceedling new <projectname>"
        ○ navigate the project and execute "ceedling test:all"
        ○ note that source codes must be in "src" folder
        ○ You can confirm that Ceedling knows about your source files by running "ceedling files:source"
        ○ ceedling module:create[<newmodulename>]
        ○ ceedling test:all --> again to see errors
```

6. Github Actions (GHA)
```
check "general_tests.yml".
This is basic but really good example of how to check your repository out, pull your docker from docker-hub and re-build docker it to use it while testing, clang execution in docker, github status ckecks in the docker, spint check in the docker, build the app in the docker, execute unit tests in the docker, check out and use thirt party repo for another linting tests and use marketplace actions like hadolint to lint the dockerfile.
```

7. bitbake
```
check "general_tests.yml".
It shows how to execute the bitbake to test and build purposes. Also, pleae check Dockerfile because it has all necessary commands to set the bitbake up inside the docker.
In this project, bitbake structure has 2 layers like meta-test and meta-build. Also, meta-build has 2 classes to compile the project with g++ and gcc.
```

8. docker
```
check "Dockerfile".
```

9. python example
```
check "custom_echo" folder.
```

10. pytest
```
check "custom_echo" folder.
```

11. glibc best practices
```
check "glibc" folder.
```

12. documents
```
check "docs" folder for general engineering/coding tips.
```

This is completely FREE project.
