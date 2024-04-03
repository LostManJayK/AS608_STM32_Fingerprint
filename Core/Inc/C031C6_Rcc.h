#ifndef C031C6_RCC_H
#define C031C6_RCC_H

#include <stdint.h>

//RCC----------------------------------------------------------------------------------------------
#define RCC (uint32_t volatile *)0x40021000U //Beginning of RCC register

//RCC_CR Clock control register
#define RCC_CR 0x00U //Offset fo rRCC_CR register
#define RCC_CR_RST 0x00000500U //Reset register
#define RCC_CR_HSEON (1U << 16) //Enable high speed external clock
#define RCC_CR_HSERDY (1U << 17) //Use bitwise AND to determine HSE ready

//RCC_APBENR1 Advanced Peripheral Bus Enable Register 1
#define RCC_APBENR1 0x3CU //Offset
#define RCC_APBENR1_RST 0x00000000U //Reset
#define RCC_APBENR1_USART2EN (1U << 17) //Enable USART2 Clock
#define RCC_APBENR1_PWREN (1U << 28) //Power interface clock enable

//RCC_APBENR2 Advanced Peripheral Bus Enable Register 2
#define RCC_APBENR2 0x40U
#define RCC_APBENR2_RST 0x00000000U //Reset
#define RCC_APBENR2_USART1EN (1U << 15) //Enable USART1 Clock

//RCC_AHBENR Advanced High-Performance Bus Enable Register
#define RCC_AHBENR 0x38U //Offset
#define RCC_AHBENR_RST 0x00000100U //Reset
#define RCC_AHBENR_DMA1EN (1U << 0) //Enable DMA1

//RCC_ICSCR RCC Internal Clock Source Calibration Register
#define RC_ICSCR 0x04U //Offset
#define RCC_ICSCR_HSICAL 0x40U //Set HSI Calibration value ot 64

//RCC_CFGR RCC Configure Register
#define RCC_CFGR 0x08U //Offset
#define RCC_CFGR_RST 0X00000000U
#define RCC_CFGR_HPRE (0b1111U<< 8) //AHB Prescaler
#define RCC_CFGR_PPRE (0b111U << 12) //APB Prescaler

//System clock switch set to HSE
#define RCC_CFGR_SW (0b110U << 0) 
#define RCC_CFGR_SWS (0b110U << 3) //System clock switch status to detect HSE ready

//RCC_IOPENR RCC I/O port clock enable register
#define RCC_IOPENR 0x34U //RCC_IOPENR Offset
#define RCC_IOPENR_RST 0x00000000U //RCC_IOPENR Reset

#define RCC_IOPENR_GPIOAEN 0b1U //Enable GPIOA clock
#define RCC_IOPENR_GPIOBEN 0b10U //Enable GPIOB clock

//FLASH--------------------------------------------------------------------------------------------
#define FLASH (uint32_t volatile *)0x40022000U

//FLASH_ACR Flash Access Control Register--------------------------------------------------------
#define FLASH_ACR 0x00U //FLASH Acces Control Register Offset
#define FLASH_ACR_RST 0x00040600U //Reset Flash AC
#define FLASH_ACR_ICEN 0x200U //Enable instruction cache
#define FLASH_ACR_PRFTEN 0x100U //Enable Prefetch Buffer
#define FLASH_ACR_LATENCY 0b001U //Set flash latency

//Functions
void clockConfig(); //Configure required RCC registers



#endif