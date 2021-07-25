#!/bin/bash
cd /home/pi/epaper/test/c-weather/src
LD_LIBRARY_PATH=$(pwd):$LD_LIBRARY_PATH
cd /home/pi/epaper/test/bcm2835
export LD_LIBRARY_PATH
