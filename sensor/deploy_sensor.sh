#!/bin/bash

if [ "$APMASKIN_IP" != "" ] && [ "APMASKIN_USERNAME" != "" ]; then
   set -e
    build_rpi.sh
    echo "Compilation done, transferring"
    scp bin/debug/SensorApp $APMASKIN_USERNAME@$APMASKIN_IP:/home/$APMASKIN_USERNAME
    ssh $APMASKIN_USERNAME@$APMASKIN_IP "./SensorApp"
else
  echo "Shell variables 'APMASKIN_IP' and 'APMASKIN_USERNAME' must be set for this to work!"
fi
