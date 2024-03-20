DESCRIPTION = "Recipe to test ReadPeriodic"
PR = "r1"

do_build () {
    valgrind --leak-check=full --show-leak-kinds=all ./bitbake_app.exe
}
