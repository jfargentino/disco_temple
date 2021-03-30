#!/bin/sh
STM32CUBEPROG_PATH=/opt/st/STM32CubeProgrammer/bin
LD_LIBRARY_PATH=. ./ST-LINK_gdbserver -cp $STM32CUBEPROG_PATH $*
