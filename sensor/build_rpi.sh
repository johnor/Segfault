#!/bin/bash      

tools/premake4 --platform=rpi gmake
make -C build config=debug_rpi verbose=false