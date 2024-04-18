#!/bin/bash

openocd -f ../thirdparty/openocd/tcl/interface/stlink-v2.cfg -f ../thirdparty/openocd/tcl/target/stm32f1x.cfg

exit 0
