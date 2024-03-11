#ifndef STM32_DMA_H
#define STM32_DMA_H


//DMA1
#define DMA 0x40020000 //DMA1 base address

//DMA_ISR
#define DMA_ISR 0x00

#define DMA_ISR_TEIF3 0x800 //Transfer error interrupt
#define DMA_ISR_TCIF3 0x200 //Transfer complete interrupt
#define DMA_ISR_HTIF3 0x400 //half transfer interrupt


//DMA_CCRx
#define DMA_CCRx_RST 0x00000000

#define DMA_CCRx_EN 0b1 //Enable channel
#define DMA_CCRx_TCIE 0b10 //Enable transfer complete interupts
#define DMA_CCRx_HTIE 0b100 //Enable half transfer interrupt
#define DMA_CCRx_TEIE 0x8 //Enable transfer error interrupt
#define DMA_CCRx_DIR 0x10 //Set data direction to read from peripheral
#define DMA_CCRx_CIRC 0x20 //Enable circular mode
#define DMA_CCRx_PINC 0x40 //Peripheral increment disabled
#define DMA_CCRx_MINC 0x80 //Memory increment enabled
#define DMA_CCRx_PSIZE (0b11 << 8) //Set peripheral size
#define DMA_CCRx_MSIZE (0b11 << 10) //Set memory size
#define DMA_CCRx_PL (0b11 << 12) // Set channel priority level to low
#define DMA_CCRx_MEM2MEM (0b1 << 14) //Set memory to memory mode

//DMA_CNDTRx
#define DMA_CNDTRx_RST 0x00000000

//Channel 2
#define DMA_CCR2 (0x08 + 0x14) //Channel 3 offset
#define DMA_CNDTR2 (0x0C + 0x14) //Data size register
#define DMA_CPAR2 (0x10 + 0x14) //Perisheral Addresss register
#define DMA_CMAR2 (0x14 + 0x14) //Memory address register


//Channel 3
#define DMA_CCR3 (0x08 + 0x28) //Channel 3 offset
#define DMA_CNDTR3 (0x0C + 0x28) //Data size register
#define DMA_CPAR3 (0x10 + 0x28) //Perisheral Addresss register
#define DMA_CMAR3 (0x14 + 0x28) //Memory address register


//Functions
void DMA1_Init3(); //Initialization for DMA1 channel 3
void DMA1_Config3(uint32_t periphAddr, uint32_t memAddr, uint32_t dataSize); //Configuration for DMA1 channel 3
void DMA1_IRQHandler3(); //DMA1 interrupt handler

#endif