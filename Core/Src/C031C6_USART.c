#include "../Inc/C031C6_USART.h"

#include "stdint.h"

uint32_t volatile *usart1_ptr = USART1;

void UART_Config()
{
    //Reset USART Control Register 1
    *(usart1_ptr + USART_CR1) &= ~(0xFFFFFFFF - USART_CR1_RST); 
    
    //Set oversampling to oversample by 8
    *(usart1_ptr + USART_CR1) &= ~(USART_CR1_OVER8);

    //Set BAUD rate to 9600
    *(usart1_ptr + USART_BRR) |= USART_BRR_BRR;

    //Set stop bits to 1 stop bit
    *(usart1_ptr + USART_CR2) &= ~((0xFF - USART_CR2_STOP) << 12);

    //Enable RX FIFO not empty interrupt
    *(usart1_ptr + USART_CR1) |= USART_CR1_RXFNEIE;

    //Enable USART
    *(usart1_ptr + USART_CR1) |= USART_CR1_UE;

    //Enable USART TX & RX
    *(usart1_ptr + USART_CR1) |= USART_CR1_TE; //TX Enable
    *(usart1_ptr + USART_CR1) |= USART_CR1_RE; //RX Enable
}

//Handle UART data transmision
void UART_Transmit(uint8_t* tx_data, uint8_t* size)
{

    for(uint16_t i=0; i<*size; ++i)
    {   

        //Reset USART transmit data register
        *(usart1_ptr + USART_TDR) &= ~(0xFFFFFFFF - USART_TDR_RST);

        //Write data byte to usart transmit data register
        *(usart1_ptr + USART_TDR) |= *(tx_data + i);

        //Wait for transfer complete bit to be set
        while(!(*(usart1_ptr + USART_ISR) & USART_ISR_TC));

    }
}

//Handle UART data reception
void UART_Receive(uint8_t *rx_data)
{

    uint8_t rx_index = 0;

    //Wait for Receive FIFO not empty to be set
    while(!(*(usart1_ptr + USART_ISR) & USART_ISR_RXFNE));

    //Read data from the RX data register into the rx_data buffer until the FIFO register is empty
    
    while(*(usart1_ptr + USART_ISR) & USART_ISR_RXFNE)
    {
        *(rx_data + rx_index) = *(usart1_ptr + USART_RDR);
        ++rx_index;
    }

}