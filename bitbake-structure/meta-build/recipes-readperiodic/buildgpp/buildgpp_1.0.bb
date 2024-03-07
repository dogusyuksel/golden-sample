DESCRIPTION = "Recipe to build the project with g++"
PR = "r1"                       
inherit gpp                 

python do_printinfo () {
    bb.plain("details of the build can be found in the gpp class");
}

do_clean () {
    make -C ../../ReadPeriodic/ clean
}

addtask printinfo before do_build
