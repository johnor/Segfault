#!/bin/bash      

premake4 gmake
make -j4 -C build config=debug verbose=1 SensorApp
