#include "../Inc/C031C6_GPIO.h"

#include <stdint.h>

//GPIO confiuration functions
void GPIO_Config()
{
    uint32_t volatile *gpiob_ptr = GPIOB; //Define pointer for GPIOB

	*(gpiob_ptr) |= GPIOx_MODER_RST; //Reset register to 0xFFFFFFFF

    //Set the appropriate GPIO pins to alternate function

    *(gpiob_ptr + GPIOx_MODER) &= ~(GPIOx_MODER_MODEy_ALT << GPIOB_MODER_MODE6);
	*(gpiob_ptr + GPIOx_MODER) |= (GPIOx_MODER_MODEy_ALT << GPIOB_MODER_MODE6);

    *(gpiob_ptr + GPIOx_MODER) &= ~(GPIOx_MODER_MODEy_ALT << GPIOB_MODER_MODE7);
	*(gpiob_ptr + GPIOx_MODER) |= (GPIOx_MODER_MODEy_ALT << GPIOB_MODER_MODE7);

    *(gpiob_ptr + GPIOx_AFRL)  &= ~(GPIOx_AFRL_AFSEL6 | GPIOx_AFRL_AFSEL7); //Set alternate function register for GPIO pins PA2 and PA3 to alternate function 1 (USART2 TX, RX)
	*(gpiob_ptr + GPIOx_AFRL)  |= (GPIOx_AFRL_AFSEL6 | GPIOx_AFRL_AFSEL7);
}