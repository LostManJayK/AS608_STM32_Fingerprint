#include "../Inc/C031C6_Rcc.h"

//Configure required RCC registers
void clockConfig()	{
	
    uint32_t volatile *rcc_ptr = RCC;

    //Reset clock control register
    *(rcc_ptr + RCC_CR) &= RCC_CR_RST;

    //Enable HSE clock and wait until ready
    *(rcc_ptr + RCC_CR) |= (RCC_CR_HSEON);
    while(!(*(rcc_ptr + RCC_CR) & (RCC_CR_HSERDY)));


    //Reset Advanced Peripheral Bus Enable Register 1
    *(rcc_ptr + RCC_APBENR1) &= RCC_APBENR1_RST;

    //Set Advaned Peripheral Bus Power Enable bit to on
    *(rcc_ptr + RCC_APBENR1) |= (RCC_APBENR1_PWREN);


    //Reset Advanced High-Performance Bus Enable Register
    *(rcc_ptr + RCC_AHBENR) &= RCC_AHBENR_RST;

    //Set Advanced High-Performance Bus DMA1 Enable to on
    *(rcc_ptr + RCC_AHBENR) |= (RCC_AHBENR_DMA1EN);


    //Reset I/O Port Enable Register
    *(rcc_ptr + RCC_IOPENR) &= RCC_IOPENR_RST;

    //Enable GPIO Clocks GPIOA and GPIOB
    *(rcc_ptr + RCC_IOPENR) |= (RCC_IOPENR_GPIOAEN | RCC_IOPENR_GPIOBEN);


    //Configure flash prefetch and latency settings, enable instruction cache
	volatile unsigned int* flash_ptr = (volatile unsigned int*)FLASH;

    // //Reset Flash access control register
    *(flash_ptr + FLASH_ACR) |= FLASH_ACR_RST;
    *(flash_ptr + FLASH_ACR) &= FLASH_ACR_RST;

    *(flash_ptr+FLASH_ACR) |= (FLASH_ACR_PRFTEN);
    *(flash_ptr+FLASH_ACR) |= (FLASH_ACR_ICEN);
    *(flash_ptr+FLASH_ACR) |= (FLASH_ACR_LATENCY);


    //Reset RCC Clock Configure Register
    *(rcc_ptr + RCC_CFGR) &= RCC_CFGR_RST;

    //Configure prescalers for HCLCK and PCLCK (Set to 1 or no prescaling)
    *(rcc_ptr + RCC_CFGR) &= ~(RCC_CFGR_HPRE | RCC_CFGR_PPRE);

    //Set clock source
    *(rcc_ptr + RCC_CFGR) &= ~RCC_CFGR_SW;
	*(rcc_ptr + RCC_CFGR) |= RCC_CFGR_SW;
	*(rcc_ptr + RCC_CFGR) &= ~RCC_CFGR_SWS;
	*(rcc_ptr + RCC_CFGR) |= RCC_CFGR_SWS;
}