#!/bin/bash

if [ "$APMASKIN_IP" != "" ] && [ "APMASKIN_USERNAME" != "" ]; then
   set -e
    build_rpi.sh
    echo "Compilation done, transferring"
    scp bin/debug/SensorApp $APMASKIN_USERNAME@$APMASKIN_IP:/home/$APMASKIN_USERNAME
    ssh $APMASKIN_USERNAME@$APMASKIN_IP "chmod +x SensorApp; ./SensorApp"
    
    #copy log back
    currentdate=$(date +"D%Y-%m-%d_T%H-%M")
    logfilename=measurementslog_$currentdate.txt
    scp $APMASKIN_USERNAME@$APMASKIN_IP:/home/$APMASKIN_USERNAME/measurementslog.txt $logfilename
    echo "Copying log to $logfilename"
else
  echo "Shell variables 'APMASKIN_IP' and 'APMASKIN_USERNAME' must be set for this to work!"
fi
