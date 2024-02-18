#include "STM32_Rcc.h"


void clockConfig()
{

    //Enable HSE clock and wait until ready
    volatile unsigned int* rcc_ptr = (unsigned int*)RCC;

    *(rcc_ptr + RCC_CR) |= (RCC_CR_HSEON);
    while(!(*(rcc_ptr + RCC_CR) & (RCC_HSERDY)));

    //Set Advaned Peripheral Bus Power Enable bit to on
    *(rcc_ptr + RCC_ABPENR1) |= (RCC_APBENR1_PWREN);

    //Configure flash prefetch and latency settings, enable instruction cache
    volatile unsigned int* flash_ptr = (unsigned int*)FLASH;

    *(flash_ptr+FLASH_ACR) |= (FLASH_ACR_PRFTEN);
    *(flash_ptr+FLASH_ACR) |= (FLASH_ACR_ICEN);
    *(flash_ptr+FLASH_ACR) |= (FLASH_ACR_LATENCY);

    //Configure prescalers for HCLCK and PCLCK
    *(rcc_ptr + RCC_CFGR) |= (RCC_CFGR_HPRE | RCC_CFGR_PPRE);

    //Set clock source
    *(rcc_ptr + RCC_CFGR) |= (RCC_CFGR_SW);
    *(rcc_ptr + RCC_CFGR) |= (RCC_CFGR_SWS);
    




}