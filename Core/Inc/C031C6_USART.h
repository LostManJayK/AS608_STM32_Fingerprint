#ifndef C031C6_USART_H
#define C031C6_USART_H

#include <stdint.h>

//USART_CR1
#define USART_CR1 0x00
#define USART_CR1_RST 0x00000000

#define USART_CR1_UE 0b1 //USART Enable
#define USART_CR1_RE 0x4 //RX Enable
#define USART_CR1_TE 0x8 //TX Enable
#define USART_CR1_RXFFIE 0x80000000 //Enable RX interrupt
#define USART_CR1_FIFOEN 0x20000000 //Enable RX FIFO
#define USART_CR1_OVER8 0x8000 //Mask for OVER8 bit set to 0
#define USART_CR1_RXFNEIE 0x20 //RX FIFO Not empty interrupt enabled

//Word length M
#define USART_CR1_M0 (0b0 << 12) //Set M0 to 0
#define USART_CR1_M1 (0b0 << 28) //Set M1 to 0

#define USART_CR1_PCE (0b0 << 10) //Disable parity control


//USART_CR2
#define USART_CR2 0x04 //Offset
#define USART_CR2_RST 0x00000000 //Reset

#define USART_CR2_STOP 0x00 //Set stop bit to one stope bit

//USART Baud Rate Register
#define USART_BRR 0x0C //Offset

#define USART_BRR_BRR 0x2710 //Set BAUD rate to 9600 (USARTDIV = 2 * f/baud)


//USART_ISR
#define USART_ISR 0x1C //Offset
#define USART_ISR_RST 0x008000C0

#define USART_ISR_TC 0x40 //Transfer Complete bit set
#define USART_ISR_TXFE 0x800000 //Tansfer FIFO empty bit set
#define USART_ISR_RXFNE 0x20 //Receive FIFO NOT empty bit set


//USART_TDR
#define USART_TDR 0x28 //Offset
#define USART_TDR_RST 0x00000000 //Reset mask

//USART_RDR
#define USART_RDR 0x24 //Offset
#define USART_RDR_RST 0x00000000


//USART1
#define USART1 (uint32_t volatile *)0x40013800 //USART1 Base Address

//Function
void UART_Config(); //Initialize and configure UART connection
void UART_Transmit(uint8_t *tx_data, uint8_t *size); //Transmit size bytes of data through USART
void UART_Receive(uint8_t *rx_data); //Receive data







#endif