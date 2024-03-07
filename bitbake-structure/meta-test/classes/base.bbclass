addtask build
do_build[dirs] = "${TOPDIR}"
do_build[nostamp] = "1"
python base_do_build () {
    bb.note("The included, default BB base.bbclass does not define a useful default task.")
    bb.note("Try running the 'listtasks' task against a .bb to see what tasks are defined.")
}

addtask do_dirtycheck
addtask do_formatcheck
addtask do_lintcheck
addtask do_unittest

EXPORT_FUNCTIONS do_build
