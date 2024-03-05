#include "C031C6_DMA.h"
#include "C031C6_Rcc.h"

//This functions performs basic initialization for the DMA1 channel 3
void DMAInit3()
{
    uint32_t *dma_ptr = (uint32_t*)DMA; //Define pointer for direct memory access base address
    uint32_t *rcc_ptr = (uint32_t*)RCC; //Define pointer for Clock control register base addess

    *(rcc_ptr + RCC_AHBENR) |= RC_AHBENR_DMA1EN; //Enable DMA1 clock


    //Channel 3 setup
    *(dma_ptr + DMA_CCR3) |= (DMA_CCRx_TCIE | DMA_CCRx_HTIE | DMA_CCRx_TEIE); //Enable DMA channel interrupts
    *(dma_ptr + DMA_CCR3) &= ~(DMA_CCRx_DIR); //Set DMA direction to read from peripheral
    *(dma_ptr + DMA_CCR3) |= (DMA_CCRx_CIRC); //Enable circular mode
    *(dma_ptr + DMA_CCR3) &= ~(DMA_CCRx_PINC); //Disable periphereal increment
    *(dma_ptr + DMA_CCR3) |= (DMA_CCRx_MINC); //Enable memory increment
    *(dma_ptr + DMA_CCR3) &= ~(DMA_CCRx_PSIZE | DMA_CCRx_MSIZE); //Set peripheral and memory data size to 8 bits
    *(dma_ptr + DMA_CCR3) &= ~(DMA_CCRx_PL); //Set priority level to low
    *(dma_ptr + DMA_CCR3) &= ~(DMA_CCRx_MEM2MEM); //Disable memory to memory mode
}

//This function performs application specific config for the DMA
void DMAConfig(uint32_t periphAddr, uint32_t memAddr, uint32_t dataSize)
{
    uint32_t *dma_ptr = (uint32_t*)DMA;

    *(dma_ptr + DMA_CNDTR3) |= datasize; //Set data transfer size

    *(dma_ptr + DMA_CPAR3) |= periphAddr; //Set peripheral address

    *(dma_ptr + DMA_CMAR3) |= memAddr; //Set memory address

    *(dma_ptr + DMA_CCR3) |= 0b1; //Enable DMA1 Channel 3
}


