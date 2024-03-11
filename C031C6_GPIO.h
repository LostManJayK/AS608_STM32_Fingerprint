#ifndef C031C6_GPIO_H
#define C031C6_GPIO_H

//GPIOx_MODER
#define GPIOx_MODER 0x00 //Offset
#define GPIOx_MODER_RST 0xFFFFFFFF //GPIOx reset value for all ports other than GPIOA
#define GPIOx_MODER_MODEy_ALT 0b10 //Set pinmode to alternate function. Must be shifter by twice the pin number

//GPIOx_AFRL GPIO Alternate Function Register Low
#define GPIOx_AFRL 0x20 //Register offset
#define GPIOx_AFRL_AFSEL2 (0b0001 << 8) //Select GPIO Pin PA2 alternate function to AF1 (USART2_TX)
#define GPIOx_AFRL_AFSEL3 (0b0001 << 12) //Select GPIO Pin PA3 alternate function to AF1 (USART2_RX)

#define GPIOx_AFRL_AFSEL6 (0b0000 << 24) //Select GPIO Pin PB6 alternate function to AF0 (USART1_TX)
#define GPIOx_AFRL_AFSEL7 (0b0000 << 28) //Select GPIO Pin PB7 alternate function to AF0 (USART1_RX)


//GPIOA
#define GPIOA 0x50000000 //Base address for GPIOA
#define GPIOA_MODER_RST 0xEBFFFFFF //Reset value for GPIOA
#define GPIOA_MODER_MODE2 4 //Pin PA2 for uart2 TX
#define GPIOA_MODER_MODE3 6 //Pin PA3 for uart2 RX

//GPIOB
#define GPIOB 0x50000400 //Basse address for GPIOB
#define GPIOB_MODER_MODE6 12 //Pin PB6 for uart TX
#define GPIOB_MODER_MODE7 14 //Pin PB7 for uart RX


void GPIOA_Config();
void GPIOB_Config();

#endif