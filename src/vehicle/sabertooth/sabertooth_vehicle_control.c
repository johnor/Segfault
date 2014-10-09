#include "vehicle_control.h"
#include "sabertooth_simplified_communication.h"
#include <math.h>
#include <stdlib.h>

static void updateRawSpeeds(void);
static double vehicleSpeedToRawSpeed(double vehicleSpeed);
static double vehicleTurnRateToRawSpeed(double vehicleTurnRate);
static int saturateRawSpeed(int speed);

const double TURN_RATE_FACTOR = 0.5;

static int currentSignedSpeed = 0;
static int currentSignedTurnRate = 0;

void setVehicleSpeed(int newSignedSpeed)
{
  if (abs(newSignedSpeed) <= VEHICLE_MAX_SPEED_MAGNITUDE)
  {
    currentSignedSpeed = newSignedSpeed;
    updateRawSpeeds();
  }
}

void setVehicleTurnRate(int newSignedTurnRate)
{
  if (abs(newSignedTurnRate) <= VEHICLE_MAX_TURN_RATE_MAGNITUDE)
  {
    currentSignedTurnRate = newSignedTurnRate;
    updateRawSpeeds();
  }
}

static void updateRawSpeeds(void)
{
  double rawSpeedTerm = vehicleSpeedToRawSpeed(currentSignedSpeed);
  double rawTurnRateTerm = vehicleTurnRateToRawSpeed(currentSignedTurnRate);

  int rawLeftSpeed = round(rawSpeedTerm + rawTurnRateTerm);
  int rawRightSpeed = round(rawSpeedTerm - rawTurnRateTerm);

  int saturatedRawLeftSpeed = saturateRawSpeed(rawLeftSpeed);
  int saturatedRawRightSpeed = saturateRawSpeed(rawRightSpeed);

  setSabertoothSpeedLeft(saturatedRawLeftSpeed);
  setSabertoothSpeedRight(saturatedRawRightSpeed);
}

static double vehicleSpeedToRawSpeed(double vehicleSpeed)
{
  return (vehicleSpeed * SABERTOOTH_MAX_SPEED_MAGNITUDE) / (double)VEHICLE_MAX_SPEED_MAGNITUDE;
}

static double vehicleTurnRateToRawSpeed(double vehicleTurnRate)
{
  return (TURN_RATE_FACTOR * vehicleTurnRate * SABERTOOTH_MAX_SPEED_MAGNITUDE) / (double)VEHICLE_MAX_TURN_RATE_MAGNITUDE;
}

static int saturateRawSpeed(int speed)
{
  int saturatedSpeed;
  if (speed > SABERTOOTH_MAX_SPEED_MAGNITUDE)
  {
    saturatedSpeed = SABERTOOTH_MAX_SPEED_MAGNITUDE;
  }
  else if (speed < -SABERTOOTH_MAX_SPEED_MAGNITUDE)
  {
    saturatedSpeed = -SABERTOOTH_MAX_SPEED_MAGNITUDE;
  }
  else
  {
    saturatedSpeed = speed;
  }
  return saturatedSpeed;
}
