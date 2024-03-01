#ifndef STM32_RCC_H
#define STM32_RCC_H

//RCC----------------------------------------------------------------------------------------------
#define RCC 0x40021000 //Beginning of RCC register

//RCC_CR Clock control register
#define RCC_CR 0x00 //Offset fo rRCC_CR register
#define RCC_CR_RST 0x00000500 //Reset register
#define RCC_CR_HSEON 0x10000 //Enable high speed external clock
#define RCC_CR_HSERDY 0x20000 //Use bitwise AND to determine HSE ready

//RCC_APBENR1 Advanced Peripheral Bus Enable Register 1
#define RCC_APBENR1 0x3C //OffseT
#define RCC_APBENR1_USART2EN 0x20000 //Enable USART2 Clock
#define RCC_APBENR1_PWREN 0x10000000 //Power interface clock enable

//RCC_APBENR2 Advanced Peripheral Bus Enable Register 2
#define RCC_APBENR2 0x40
#define RCC_APBENR2_USART1EN 0x8000

//RCC_ICSCR RCC Internal Clock Source Calibration Register
#define RC_ICSCR 0x04 //Offset
#define RCC_ICSCR_HSICAL 0x40 //Set HSI Calibration value ot 64

//RCC_CFGR RCC Configure Register
#define RCC_CFGR 0x08
#define RCC_CFGR_HPRE 0x0 //AHB Prescaler set to 1
#define RCC_CFGR_PPRE 0x0 //APB Prescaler set to 1
#define RCC_CFGR_SW 0b001 //System clock switch set to HSE
#define RCC_CFGR_SWS 0b001 //System clock switch status to detect HSE ready

//FLASH--------------------------------------------------------------------------------------------
#define FLASH 0x40022000

//FLASH_ACR Flash Access Control Register--------------------------------------------------------
#define FLASH_ACR 0x00 //FLASH Acces Control Register Offset
#define FLASH_ACR_RST 0x00040600 //Reset Flash AC
#define FLASH_ACR_ICEN 0x200 //Enable instruction cache
#define FLASH_ACR_PRFTEN 0x100 //Enable Prefetch Buffer
#define FLASH_ACR_LATENCY 0b001 //Set flash latency


void clockConfig();



#endif