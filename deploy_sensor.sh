#!/bin/bash

if [ "$SEGFAULT_IP" != "" ] && [ "SEGFAULT_USERNAME" != "" ]; then
   set -e
    build_rpi.sh
    echo "Compilation done, transferring"
    scp bin/debug/SensorApp $SEGFAULT_USERNAME@$SEGFAULT_IP:/home/$SEGFAULT_USERNAME
    ssh $SEGFAULT_USERNAME@$SEGFAULT_IP "chmod +x SensorApp; ./SensorApp"
    
    #copy log back
    currentdate=$(date +"D%Y-%m-%d_T%H-%M")
    logfilename=measurementslog_$currentdate.txt
    scp $SEGFAULT_USERNAME@$SEGFAULT_IP:/home/$SEGFAULT_USERNAME/measurementslog.txt $logfilename
    echo "Copying log to $logfilename"
else
  echo "Shell variables 'SEGFAULT_IP' and 'SEGFAULT_USERNAME' must be set for this to work!"
fi
