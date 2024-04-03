#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"

 #include "Core/Inc/C031C6_Rcc.h"
 #include "Core/Inc/C031C6_GPIO.h"
#include "Core/Inc/C031C6_USART.h"

void delay();

int main()
{

	clockConfig();
	GPIO_Config();
	UART_Config();
	
	uint8_t size = 4; //Max 255
    uint8_t *data = (uint8_t*)malloc(size * sizeof(uint8_t));

	for (uint8_t i = 0; i<4; ++i)
	{
		*(data + i) = "TEST"[i];
	}
    

    while(1)
    {
        UART_Transmit(data, (uint8_t*)&size);
        delay();

    };

	free(data);
}



void delay()
{
    unsigned int counter = 0;

    while(counter++ < 10000);
}