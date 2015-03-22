#!/bin/bash      

tools/premake4 gmake

command="SensorApp"

if [[ -n $1 ]]
then :
   command=$1
fi
echo "Running make on target $command"
make -j4 -C build config=debug_rpi verbose=false $command