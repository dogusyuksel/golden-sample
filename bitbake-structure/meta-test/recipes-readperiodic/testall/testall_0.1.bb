DESCRIPTION = "Recipe to test ReadPeriodic"
PR = "r1"

do_dirtycheck () {
    PWD=$(pwd)
    cd ../../scripts
    ./dirty_check.sh
    cd $PWD
}

do_formatcheck () {
    PWD=$(pwd)
    cd ../../scripts
    ./format_check.sh
    cd $PWD
}

do_lintcheck () {
    PWD=$(pwd)
    cd ../../scripts
    ./lint_check.sh
    cd $PWD
}

do_unittest () {
    PWD=$(pwd)
    cd ../../scripts
    ./run_unittests.sh
    cd $PWD
}

do_build () {
    PWD=$(pwd)
    cd ../../scripts
    ./dirty_check.sh
    ./format_check.sh
    ./lint_check.sh
    ./run_unittests.sh
    cd $PWD
}
