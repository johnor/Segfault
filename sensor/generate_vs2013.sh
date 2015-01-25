#!/bin/bash      

tools/premake4 vs2013

if [ $1 = "--open" ] 
then :
   start build/Sensor.sln
fi