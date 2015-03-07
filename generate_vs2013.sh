#!/bin/bash      

tools/premake4 vs2013

mode=$1

if [[ $mode = "--open" ]]
then :
   start build/Sensor.sln
fi