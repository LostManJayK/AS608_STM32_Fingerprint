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

//RCC_AHBENR Advanced High-Performance Bus Enable Register
#define RCC_AHBENR 0x38
#define RCC_AHBENR_DMA1EN 0b1

//RCC_ICSCR RCC Internal Clock Source Calibration Register
#define RC_ICSCR 0x04 //Offset
#define RCC_ICSCR_HSICAL 0x40 //Set HSI Calibration value ot 64

//RCC_CFGR RCC Configure Register
#define RCC_CFGR 0x08
#define RCC_CFGR_HPRE (0b0000<< 8) //AHB Prescaler
#define RCC_CFGR_PPRE (0b000 << 12) //APB Prescaler
#define RCC_CFGR_SW 0b001 //System clock switch set to HSE
#define RCC_CFGR_SWS 0b001 //System clock switch status to detect HSE ready

//RCC_IOPENR RCC I/O port clock enable register
#define RCC_IOPENR 0x34 //RCC_IOPENR Offset
#define RCC_IOPENR_RST 0x00000000 //RCC_IOPENR Reset

#define RCC_IOPENR_GPIOAEN 0b1 //Enable GPIOA clock
#define RCC_IOPENR_GPIOBEN 0b10 //Enable GPIOB clock

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