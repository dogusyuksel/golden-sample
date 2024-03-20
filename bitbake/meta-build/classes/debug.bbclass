addtask build
addtask clean

debug_do_build () {
    echo "Building with debug..."
    gcc ../main.c -DDEBUG_ENABLED -o bitbake_buildapp.exe
}

EXPORT_FUNCTIONS do_build
