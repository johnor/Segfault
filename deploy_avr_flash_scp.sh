#!/bin/bash

set -e

make -C src/avr


if [ "$APMASKIN_IP" != "" ] && [ "APMASKIN_USERNAME" != "" ]; then
  echo "Apmaskin IP is: $APMASKIN_IP, pinging..."

  set +e
  ping -c 1 -W 2 $APMASKIN_IP
  
  if [ $? != 0 ]; then
    echo "No Apmaskin!"
  else
    echo "Apmaskin is available! Transferring..."
    set -e
    
    if [[ $1 == "--flash" ]]; then
	    scp src/avr/gertboard_avr.hex $APMASKIN_USERNAME@$APMASKIN_IP:/home/$APMASKIN_USERNAME/gertboard/gertboard_avr.hex
	    scp src/avr/Makefile $APMASKIN_USERNAME@$APMASKIN_IP:/home/$APMASKIN_USERNAME/gertboard/Makefile
	    ssh $APMASKIN_USERNAME@$APMASKIN_IP "make -C /home/$APMASKIN_USERNAME/gertboard flash"
    fi
    
    arm-bcm2708hardfp-linux-gnueabi-gcc -o src/avr/test_i2c src/avr/test_i2c.c -Ilib/wiringPi -Llib/wiringPi -lwiringPi
    scp src/avr/test_i2c $APMASKIN_USERNAME@$APMASKIN_IP:/home/$APMASKIN_USERNAME/gertboard/test_i2c
    ssh $APMASKIN_USERNAME@$APMASKIN_IP "cd gertboard && sudo ./test_i2c"
    
    echo "Transfer and flashing done!"
  fi
else
  echo "Shell variables 'APMASKIN_IP' and 'APMASKIN_USERNAME' must be set for this to work!"
fi
