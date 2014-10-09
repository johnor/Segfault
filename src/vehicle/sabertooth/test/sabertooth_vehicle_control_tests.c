#include "unity.h"
#include "vehicle_control.h"
#include "mock_sabertooth_simplified_communication.h"

void resetSpeedAndTurning(void);

void setUp(void)
{
  resetSpeedAndTurning();
}

void resetSpeedAndTurning(void)
{
  /* Cannot use Ignore since it will ignore all subsequent calls in the tests */

  setSabertoothSpeedLeft_Expect(0);
  setSabertoothSpeedLeft_IgnoreArg_speedLeft();
  setSabertoothSpeedRight_Expect(0);
  setSabertoothSpeedRight_IgnoreArg_speedRight();

  setVehicleSpeed(0);

  setSabertoothSpeedLeft_Expect(0);
  setSabertoothSpeedLeft_IgnoreArg_speedLeft();
  setSabertoothSpeedRight_Expect(0);
  setSabertoothSpeedRight_IgnoreArg_speedRight();

  setVehicleTurnRate(0);
}

void tearDown(void)
{
}

void test_setSpeedSetsSabertoothSpeeds(void)
{
  int speed = 27;
  setSabertoothSpeedLeft_Expect(0);
  setSabertoothSpeedLeft_IgnoreArg_speedLeft();
  setSabertoothSpeedRight_Expect(0);
  setSabertoothSpeedRight_IgnoreArg_speedRight();

  setVehicleSpeed(speed);
}

void test_turnVehicleSetsSabertoothSpeeds(void)
{
  int turnRate = 2;
  setSabertoothSpeedLeft_Expect(0);
  setSabertoothSpeedLeft_IgnoreArg_speedLeft();
  setSabertoothSpeedRight_Expect(0);
  setSabertoothSpeedRight_IgnoreArg_speedRight();

  setVehicleTurnRate(turnRate);
}

void test_speedsAreSetCorrectlyWhenGoingStraight(void)
{
  int speed = 0;
  setSabertoothSpeedLeft_Expect(0);
  setSabertoothSpeedRight_Expect(0);
  setVehicleSpeed(speed);

  speed = 100;
  // 100% of 63 (MAX)
  setSabertoothSpeedLeft_Expect(63);
  setSabertoothSpeedRight_Expect(63);
  setVehicleSpeed(speed);

  speed = -100;
  // 100% of -63 (MIN)
  setSabertoothSpeedLeft_Expect(-63);
  setSabertoothSpeedRight_Expect(-63);
  setVehicleSpeed(speed);

  speed = 5;
  // 5% of 63 (MAX)
  setSabertoothSpeedLeft_Expect(3);
  setSabertoothSpeedRight_Expect(3);
  setVehicleSpeed(speed);

  speed = -90;
  // 90% of -63 (MIN)
  setSabertoothSpeedLeft_Expect(-57);
  setSabertoothSpeedRight_Expect(-57);
  setVehicleSpeed(speed);

  speed = 72;
  // 72% of 63 (MAX)
  setSabertoothSpeedLeft_Expect(45);
  setSabertoothSpeedRight_Expect(45);
  setVehicleSpeed(speed);
}

void test_speedsAreSetCorrectlyWhenOnlyTurning(void)
{
  int turnRate = 0;
  setSabertoothSpeedLeft_Expect(0);
  setSabertoothSpeedRight_Expect(0);
  setVehicleTurnRate(turnRate);

  turnRate = 100;
  // Left: 100% of 63/2 (MAX/2)
  // Right: 100% of -63/2 (MIN/2)
  setSabertoothSpeedLeft_Expect(32);
  setSabertoothSpeedRight_Expect(-32);
  setVehicleTurnRate(turnRate);

  turnRate = -100;
  // Left: 100% of -63/2 (MIN/2)
  // Right: 100% of 63/2 (MAX/2)
  setSabertoothSpeedLeft_Expect(-32);
  setSabertoothSpeedRight_Expect(32);
  setVehicleTurnRate(turnRate);

  turnRate = 7;
  // Left: 7% of 63/2 (MAX/2)
  // Right: 7% of -63/2 (MIN/2)
  setSabertoothSpeedLeft_Expect(2);
  setSabertoothSpeedRight_Expect(-2);
  setVehicleTurnRate(turnRate);

  turnRate = -20;
  // Left: 20% of -63/2 (MIN/2)
  // Right: 20% of 63/2 (MAX/2)
  setSabertoothSpeedLeft_Expect(-6);
  setSabertoothSpeedRight_Expect(6);
  setVehicleTurnRate(turnRate);
}

void test_speedsAreSetCorrectlyWhenMovingAndTurning(void)
{
  int speed = 0;
  int turnRate = 0;
  setSabertoothSpeedLeft_Expect(0);
  setSabertoothSpeedRight_Expect(0);
  setVehicleSpeed(speed);
  setSabertoothSpeedLeft_Expect(0);
  setSabertoothSpeedRight_Expect(0);
  setVehicleTurnRate(turnRate);

  speed = 5;
  setSabertoothSpeedLeft_Expect(3);
  setSabertoothSpeedRight_Expect(3);
  setVehicleSpeed(speed);

  turnRate = -40;
  setSabertoothSpeedLeft_Expect(-9);
  setSabertoothSpeedRight_Expect(16);
  setVehicleTurnRate(turnRate);

  speed = -50;
  setSabertoothSpeedLeft_Expect(-44);
  setSabertoothSpeedRight_Expect(-19);
  setVehicleSpeed(speed);

  turnRate = 2;
  setSabertoothSpeedLeft_Expect(-31);
  setSabertoothSpeedRight_Expect(-32);
  setVehicleTurnRate(turnRate);
}

void test_setSpeedIgnoresInvalidInput(void)
{
  setVehicleSpeed(101);
  setVehicleSpeed(-101);
  setVehicleSpeed(1010);
}

void test_turnVehicleIgnoresInvalidInput(void)
{
  setVehicleTurnRate(101);
  setVehicleTurnRate(-101);
  setVehicleTurnRate(999);
}

void test_motorValuesWithinBoundsWhenMaximumInput(void)
{
  int speed = 100;
  int turnRate = 100;
  setSabertoothSpeedLeft_Expect(63);
  setSabertoothSpeedRight_Expect(63);
  setVehicleSpeed(speed);
  setSabertoothSpeedLeft_Expect(63);
  setSabertoothSpeedRight_Expect(32);
  setVehicleTurnRate(turnRate);

  speed = -100;
  setSabertoothSpeedLeft_Expect(-32);
  setSabertoothSpeedRight_Expect(-63);
  setVehicleSpeed(speed);

  turnRate = -100;
  setSabertoothSpeedLeft_Expect(-63);
  setSabertoothSpeedRight_Expect(-32);
  setVehicleTurnRate(turnRate);

  speed = 100;
  setSabertoothSpeedLeft_Expect(32);
  setSabertoothSpeedRight_Expect(63);
  setVehicleSpeed(speed);
}
