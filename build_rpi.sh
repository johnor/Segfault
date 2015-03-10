#!/bin/bash      

tools/premake4 --platform=rpi gmake
make -j4 -C build config=debug_rpi verbose=false SensorApp