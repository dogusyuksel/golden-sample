DESCRIPTION = "Recipe to build the project"
PR = "r1"

do_build () {
    echo "Building..."
    gcc ../main.c -o bitbake_app.exe
}

do_clean () {
    echo "Cleaning..."
    rm -rf bitbake_app.exe
}
