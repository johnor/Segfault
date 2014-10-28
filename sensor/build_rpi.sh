#!/bin/bash      

tools/premake4 --platform=rpi gmake
make config=debug_rpi verbose=false