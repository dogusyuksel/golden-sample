addtask build

python base_do_build () {
    bb.note("The included, default BB base.bbclass does not define a useful default task.")
    bb.note("Try running the 'listtasks' task against a .bb to see what tasks are defined.")
}

addtask clean

EXPORT_FUNCTIONS do_build
