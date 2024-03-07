DESCRIPTION = "Recipe to build ReadPeriodic project with gcc"
PR = "r1"

do_build () {
    echo "BUILDING..."
    make -C ../../ReadPeriodic/ COMPILER=gcc all
}

do_clean () {
    echo "CLEANING..."
    make -C ../../ReadPeriodic/ clean
}
