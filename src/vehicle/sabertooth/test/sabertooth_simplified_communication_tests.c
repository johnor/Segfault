#include "unity.h"
#include "sabertooth_simplified_communication.h"
#include "mock_serial_port.h"

static const uint8_t leftSpeedStop = 64;
static const uint8_t rightSpeedStop = 192;

void setUp(void)
{
}

void tearDown(void)
{
}

void test_minMaxSpeedConstantsCorrect(void)
{
  TEST_ASSERT_EQUAL(63, SABERTOOTH_MAX_SPEED_MAGNITUDE);
}

void test_setSpeedLeftTransmits(void)
{
  serialPortTransmit_ExpectAndReturn(0, SERIAL_PORT_SUCCESS);
  serialPortTransmit_IgnoreArg_dataToTransmit();
  setSabertoothSpeedLeft(0);
}

void test_setSpeedRightTransmits(void)
{
  serialPortTransmit_ExpectAndReturn(0, SERIAL_PORT_SUCCESS);
  serialPortTransmit_IgnoreArg_dataToTransmit();
  setSabertoothSpeedRight(0);
}

void test_correctLeftValueIsTransmitted(void)
{
  /* Testing some boundary values */

  serialPortTransmit_ExpectAndReturn(leftSpeedStop, SERIAL_PORT_SUCCESS);
  setSabertoothSpeedLeft(0);

  serialPortTransmit_ExpectAndReturn(leftSpeedStop + SABERTOOTH_MAX_SPEED_MAGNITUDE, SERIAL_PORT_SUCCESS);
  setSabertoothSpeedLeft(SABERTOOTH_MAX_SPEED_MAGNITUDE);

  serialPortTransmit_ExpectAndReturn(leftSpeedStop - SABERTOOTH_MAX_SPEED_MAGNITUDE, SERIAL_PORT_SUCCESS);
  setSabertoothSpeedLeft(-SABERTOOTH_MAX_SPEED_MAGNITUDE);
}

void test_correctRightValueIsTransmitted(void)
{
  /* Testing some boundary values */

  serialPortTransmit_ExpectAndReturn(rightSpeedStop, SERIAL_PORT_SUCCESS);
  setSabertoothSpeedRight(0);

  serialPortTransmit_ExpectAndReturn(rightSpeedStop + SABERTOOTH_MAX_SPEED_MAGNITUDE, SERIAL_PORT_SUCCESS);
  setSabertoothSpeedRight(SABERTOOTH_MAX_SPEED_MAGNITUDE);

  serialPortTransmit_ExpectAndReturn(rightSpeedStop - SABERTOOTH_MAX_SPEED_MAGNITUDE, SERIAL_PORT_SUCCESS);
  setSabertoothSpeedRight(-SABERTOOTH_MAX_SPEED_MAGNITUDE);
}

void test_InvalidLeftValuesIgnored(void)
{
  setSabertoothSpeedLeft(SABERTOOTH_MAX_SPEED_MAGNITUDE + 1);
  setSabertoothSpeedLeft(-SABERTOOTH_MAX_SPEED_MAGNITUDE - 1);
}

void test_InvalidRightValuesIgnored(void)
{
  setSabertoothSpeedRight(SABERTOOTH_MAX_SPEED_MAGNITUDE + 1);
  setSabertoothSpeedRight(-SABERTOOTH_MAX_SPEED_MAGNITUDE - 1);
}

// TODO: Check return value of transmit and return error/log result
