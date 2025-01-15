//-----------------------------------------------------------------------------
// file name: config.h
// author: xuxin
// DATE:2025-01-09
//-----------------------------------------------------------------------------
#include <Arduino.h>

#ifndef _CONFIG_H_
#define _CONFIG_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define TEST_YES 0XA5
#define TEST_NO 0X5A
#define LED_PIN 13

 /*********arduino uno R3 *************
     *          8bit micro               *
     *** ATMega16U2 Processor: USB-シリアル変換
            16kB ISP Flash
            512B EEPROM
            512B SRAM

     *** ATMega328P Processor: AVR CPU 16 MHz     
            32 kB Flash   0x8000/boot
            2 kB SRAM     0x0800
            1 kB EEPROM   0x0400
    ********************************/

#define  INCLUDE_MODULE_PATCH TEST_YES 


#ifdef __cplusplus
}

#endif

#endif