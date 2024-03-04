#ifndef STM32_GPIO_H
#define STM32_GPIO_H


//GPIOx_MODER
#define GPIOx_MODER 0x00 //Offset
#define GPIOx_MODER_RST 0xFFFFFFFF //GPIOx reset value for all ports other than GPIOA
#define GPIOx_MODER_ALT 0b10 //Set pinmode to alternate function. Must be shifter by twice the pin number



//GPIOA
#define GPIOA 0x50000000 //Base address for GPIOA
#define GPIOA_MODER_RST 0xEBFFFFFF //Reset value for GPIOA

//GPIOB
#define GPIOB 0x50000400 //Basse address for GPIOB


//USART_CR1
#define USART_CR1 0x00
#define USART_CR1_RST 0x00000000

#define USART_CR1_UE 0b1 //USART Enable
#define USART_CR1_RE 0x4 //RX Enable
#define USART_CR1_TE 0x8 //TX Enable
#define USART_CR1_RXFFIE 0x80000000 //Enable RX interrupt
#define USART_CR1_FIFOEN 0x20000000 //Enable RX FIFO
//Word length M
#define USART_CR1_M0 (0b0 << 12) //Set M0 to 0
#define USART_CR1_M1 (0b0 << 28) //Set M1 to 0
#define USART_CR1_PCE (0b0 << 10) //Disable parity control


//USART_CR2
#define USART_CR2 0x04 //Offset
#define USART_CR2_RST 0x00000000 //Reset





//USART1
#define USART1 0x40013800 //USART1 Base Address







#endif