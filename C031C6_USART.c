#include "C031C6_USART.h"

void UART_Config()
{
    volatile uint32_t *usart1_ptr = USART1;

    unsigned int msk = *usart1_ptr; //Store the current values stored in the USART register


    *(usart1_ptr + USART_CR1) &= (uint32_t)USART_CR1_RST; //Reset USART Control Register 1
    
    //Set oversampling to oversample by 8
    *(usart1_ptr + USART_CR1) &= ~(USART_CR1_OVER8);

    //Set BAUD rate to 9600
    *(usart1_ptr + USART_BRR) |= USART_BRR_BRR;

     //Enable USART
    *(usart1_ptr + USART_CR1) |= USART_CR1_UE;

    
    //Enable USART TX & RX
    *(usart1_ptr + USART_CR1) |= USART_CR1_TE; //TX Enable
    *(usart1_ptr + USART_CR1) |= USART_CR1_RE; //RX Enable

    //

 
}