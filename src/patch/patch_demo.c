//-----------------------------------------------------------------------------
// file name: patch_demo.C
// author: xuxin
// DATE:2025-01-09
//-----------------------------------------------------------------------------
#if (INCLUDE_MODULE_PATCH == TEST_YES) 
#include "config.h"
// #include <EEPROM.h>
#include "patch_demo.h"
#include <stdio.h>

#define _OSS_DIAGDISPATCH_C_

// __attribute__((section(".fun_section"))) void my_function() {
// }
// const char message[] PROGMEM = "Hello, World!"; //PROGMEM save to flash
// __attribute__((section(".var_section"))) int my_variable = 0XA5A5;

// demo original function1(int (*)(int,float)()) for test
static int func1_orgdemo(int intParam1, float floatParam1);
// demo original function2(float (*)(double)()) for test
static float func2_orgdemo(double doubleParam);
// demo original function3(int (*)(int,float)()) for test
static int func3_orgdemo(int intParam2, float floatParam2);

// RAM jump table （fixed address）
PATCH_ST_FUNCTIONS_LIST  patch_g_ramJumptable __attribute__((aligned(2),section(".patch_ram"))) = {
    .func1 = func1_orgdemo,
    .func2 = func2_orgdemo,
    .func3 = func3_orgdemo,
};

// ROM jump table
const PATCH_ST_FUNCTIONS_LIST patch_g_romJumptbl __attribute__((aligned(2),section(".patch_rom"))) = {
    .func1 = func1_orgdemo,
    .func2 = func2_orgdemo,
    .func3 = func3_orgdemo,
};

void patch_loadJumpTable(void) {
    PATCH_EN_STATUS patchStatus = PATCH_IDLE;
    int *pJumpAddr;

    // EEPROM.get(PATCH_EEPROM_FLAG_ADDR, patchStatus);

    if (patchStatus == PATCH_LOADED){ //successfully load patch, use new jumptable
        pJumpAddr = (int *)PATCH_FLASH_JUMP_TABLE_ADDR; //loaded flash jumptable
    }
    else { //using original jumptable
        pJumpAddr = (int *)PATCH_ROM_JUMP_TABLE_ADDR; //pre loaded rom jumptable       
    }

    memcpy((int *)PATCH_RAM_JUMP_TABLE_ADDR, pJumpAddr, PATCH_JUMP_TABLE_SIZE);
}

// demo original function1(int (*)(int,float)()) for test
static int func1_orgdemo(int intParam1, float floatParam1) {
    // Serial.print("original function1(int (*)(int,float)()): intParam1=");
    for (int i = 0; i < 10; i++) {
        digitalWrite(LED_PIN, HIGH);
        delay(100);
        digitalWrite(LED_PIN, LOW);
        delay(100);
    }
    return  intParam1 + floatParam1;
}

// demo original function2(float (*)(double)()) for test
static float func2_orgdemo(double doubleParam) {
    for (int i = 0; i < 10; i++) {
        digitalWrite(LED_PIN, HIGH);
        delay(500);
        digitalWrite(LED_PIN, LOW);
        delay(500);
    }
    return doubleParam * doubleParam;
}

// demo original function3(int (*)(int,float)()) for test
static int func3_orgdemo(int intParam2, float floatParam2) {
    for (int i = 0; i < 10; i++) {
        digitalWrite(LED_PIN, HIGH);
        delay(800);
        digitalWrite(LED_PIN, LOW);
        delay(400);
    }
    return intParam2 * floatParam2;
}

// #define G_FLASH_PATCH_FLAG 0x200  //global　variable:PATCH FLAG
// EEPROM.update(address, val);


#endif