#include <stdio.h>
#include "system_i2c.h"
#include "variant.h"
#include "system_time.h"
#include "log.h"
#include "avrcommondef.h"

static const char thisIsAString[] = "This is a string";
unsigned int one = 1;
unsigned int two = 2;
unsigned int three = 3;
unsigned int twoHundredAndFiftyFive = 0xFF;
float pi = 3.14;


int main()
{
  printf("Hello Raspberry!\n");

  if (!i2c_Init(AVR_SLAVE_ADDRESS))
  {
    printf("Could not initialize i2c\n");
  }
  else
  {
    printf("i2c initialized\n");
  }

  DEBUG_PRINTF("This is a debug build\n");
  DEBUG_PRINTF("Built at: %s, %s\n", __TIME__, __DATE__);
  printf("Current time is: %s\n", getDateAndTime());
  DEBUG_PRINTF("These are numbers: %d, %f, 0x%X\n", 4, 0.75, 0xFE);
  DEBUG_PRINTF("Line number: %d\n", __LINE__);

  printf("Let's try writing something to the application log...\n");
  initiateLog();
  writeLog("This is my first log entry!\n");
  writeLog("I can log strings: \"%s\"\n", thisIsAString);
  writeLog("I can log integers: %d %d %d 0x%X\n", one, two, three, twoHundredAndFiftyFive);
  writeLog("and floats: %f\n", pi);
  printf("...done! You should now have a file called \"apmaskin<date>.log\" in the same directory as this application. "
         "Check it out! Terminating application...\n");

  printf("Writing 0xAB to slave at address 0x01\n");
  i2c_Write8(0x01, 0xAF);

  printf("Reading back data at address 0x01...\n");
  printf("Read %X\n", i2c_Read8(0x01));

  terminateLog();
  return 0;
}
