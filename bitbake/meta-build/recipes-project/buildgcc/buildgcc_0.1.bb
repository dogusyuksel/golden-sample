DESCRIPTION = "Recipe to build ReadPeriodic project with gcc"
PR = "r1"

do_build () {
    echo "Building..."
    gcc ../main.c -o bitbake_app.exe
}

do_clean () {
    echo "Cleaning..."
    rm -rf bitbake_app.exe
}
