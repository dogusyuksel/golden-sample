DESCRIPTION = "Recipe to build the project with g++"
PR = "r1"                       
inherit debug                 

python do_printinfo () {
    bb.plain("details of the build can be found in the debug class");
}

do_clean () {
    rm -rf bitbake_buildapp.exe
}

addtask printinfo before do_build
