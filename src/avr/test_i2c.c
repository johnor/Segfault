#include <wiringPiI2C.h>
#include <stdio.h>
#include "avrcommondef.h"

int main()
{

  int xio = wiringPiI2CSetup (AVR_SLAVE_ADDRESS);
  if (xio < 0)
  {
    printf ("Unable to initialize I2C\n");
    return 1;
  }

printf("Data0: %X\n", wiringPiI2CReadReg8(xio, 0));
printf("Data1: %X\n", wiringPiI2CReadReg8(xio, 1));
printf("Data2: %X\n", wiringPiI2CReadReg8(xio, 2));
printf("Data3: %X\n", wiringPiI2CReadReg8(xio, 3));
printf("Data4: %X\n", wiringPiI2CReadReg8(xio, 4));
printf("Data5: %X\n", wiringPiI2CReadReg8(xio, 5));


printf("Data0-16: %X\n", wiringPiI2CReadReg16(xio, 0));

wiringPiI2CWriteReg8(xio, 0, 0xAA);
wiringPiI2CWriteReg8(xio, 1, 0xBB);
wiringPiI2CWriteReg8(xio, 2, 0xCC);
wiringPiI2CWriteReg16(xio, 3, 0xEEDD);

printf("Data0: %X\n", wiringPiI2CReadReg8(xio, 0));
printf("Data1: %X\n", wiringPiI2CReadReg8(xio, 1));
printf("Data2: %X\n", wiringPiI2CReadReg8(xio, 2));
printf("Data3: %X\n", wiringPiI2CReadReg8(xio, 3));
printf("Data4: %X\n", wiringPiI2CReadReg8(xio, 4));
printf("Data5: %X\n", wiringPiI2CReadReg8(xio, 5));

printf("Data0-16: %X\n", wiringPiI2CReadReg16(xio, 0));

return 0;
}
