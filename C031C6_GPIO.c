#include "C031C6_GPIO.h"
#include "C031C6_Rcc.h"

//GPIO confiuration functions
void GPIOA_Config()
{
    uint32_t *gpio_ptr = GPIOA; //Define pointer for GPIOA

    //Set the appropriate GPIO pins to alternate function
    *(gpioa_ptr + GPIOx_MODER) |= (GPIOx_MODER_MODEy_ALT << GPIOA_MODER_MODE2);
    *(gpioa_ptr + GPIOx_MODER) |= (GPIOx_MODER_MODEy_ALT << GPIOA_MODER_MODE3);
    *(gpioa_ptr + GPIOx_AFRL)  |= (GPIOx_AFRL_AFSEL2 | GPIOx_AFRL_AFSLE3) //Set alternate function register for GPIO pins PA2 and PA3 to alternate function 1 (USART2 TX, RX)
}