#!/bin/bash

set -euo pipefail

bitbake gpio && bitbake gpio:do_clean
bitbake uartrtc && bitbake uartrtc:do_clean
bitbake adcdma && bitbake adcdma:do_clean


exit 0
