import sys
import time

import cecho

echo = cecho.Cecho("")

if len(sys.argv) != 1:

    str = ""
    word_counter = 0

    for word in sys.argv:

        if word_counter == 0:

            word_counter = word_counter + 1
            continue

        str = str + " " + sys.argv[word_counter]
        word_counter = word_counter + 1

    echo = cecho.Cecho(str)

ret_val = echo.echo()

time.sleep(3)

if ret_val is True:
    sys.exit(0)

sys.exit(1)
