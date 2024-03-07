addtask build
addtask clean

gpp_do_build () {
    echo "BUILDING g++..."
    make -C ../../ReadPeriodic/ COMPILER=g++ all
}

EXPORT_FUNCTIONS do_build
