#include "sabertooth_simplified_communication.h"
#include "serial_port.h"

static const int LEFT_STOP_VALUE = 64;
static const int RIGHT_STOP_VALUE = 192;

void setSabertoothSpeedLeft(int speedLeft)
{
  if (speedLeft >= -SABERTOOTH_MAX_SPEED_MAGNITUDE && speedLeft <= SABERTOOTH_MAX_SPEED_MAGNITUDE)
  {
    serialPortTransmit(LEFT_STOP_VALUE + speedLeft);
  }
}

void setSabertoothSpeedRight(int speedRight)
{
  if (speedRight >= -SABERTOOTH_MAX_SPEED_MAGNITUDE && speedRight <= SABERTOOTH_MAX_SPEED_MAGNITUDE)
  {
    serialPortTransmit(RIGHT_STOP_VALUE + speedRight);
  }
}
