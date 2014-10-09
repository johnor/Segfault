#include <stdio.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "i2c_slave.h"
#include "avrcommondef.h"

int main(void)
{
    uart_init();
    I2C_init(AVR_SLAVE_ADDRESS);

    I2C_writeData(0, 1);
    I2C_writeData(1, 2);
    I2C_writeData(2, 3);
    I2C_writeData(3, 4);
    I2C_writeData(4, 5);

    sei();

    stdout = &uart_output;
    stdin  = &uart_input;

    char input;

    while(1)
    {
        input = getchar();
        printf("You wrote %c\n", input);
        printf("buffer0: %i\n", I2C_readData(0));
        printf("buffer1: %i\n", I2C_readData(1));
        printf("buffer2: %i\n", I2C_readData(2));
        printf("buffer3: %i\n", I2C_readData(3));
        printf("buffer4: %i\n", I2C_readData(4));
    }

    return 0;
}
