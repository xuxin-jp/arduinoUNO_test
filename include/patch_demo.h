//-----------------------------------------------------------------------------
// file name: patch_demo.h
// author: xuxin
// DATE:2025-01-09
//-----------------------------------------------------------------------------
   
#if (INCLUDE_MODULE_PATCH == TEST_YES) 

#ifndef _PATCH_DEMO_H_
#define _PATCH_DEMO_H_

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef _PATCH_DEMO_C_
#define TEST_EXT
#else
#define TEST_EXT extern
#endif

#define LED_PIN 13

/*** ATMega328P Processor: AVR CPU 16 MHz     
    32 kB Flash   0x8000/boot
    2 kB SRAM     0x0800
    1 kB EEPROM   0x0400
********************************/
#define  PATCH_JUMP_TABLE_SIZE       0x100  // 64/2 = 32 functions /sizeof(PATCH_ST_FUNCTIONS_LIST)

#define  PATCH_RAM_JUMP_TABLE_ADDR   0x800 // pre-fixed address  platformioini/my_linker_param.ld
#define  PATCH_ROM_JUMP_TABLE_ADDR   0x6200  // original jumptable & program 

#define  PATCH_FLASH_JUMP_TABLE_ADDR 0x6400 // new jumptable
#define  PATCH_FLASH_PATCH_ZONE_SIZE 0x0400 // patch code size 
#define  PATCH_FLASH_PATCH_CODE_ADDR 0x6600 // patch code

#define  PATCH_EEPROM_FLAG_ADDR      0x00 // e2prom flag address , patch status


// patch status
typedef enum patchStausEN{
  PATCH_IDLE,
  PATCH_READY = 0X5A,
  PATCH_LOADED = 0XA5
}PATCH_EN_STATUS;

typedef struct functionListST{
    int (*func1)(int, float);
    float (*func2)(double);
    int (*func3)(int, float);
}PATCH_ST_FUNCTIONS_LIST;

// // 生成通用包装器函数
// DEFINE_WRAPPER(func1, int, int a, float b)
// DEFINE_WRAPPER(func2, float, double x)
// DEFINE_WRAPPER(func3, int, int a, float b)

// reset and load jump table to ram jumptable
void patch_loadJumpTable(void);

#define CALL_FUNCTION(func_name, ...)                              \
    do {                                                           \
        if (((PATCH_ST_FUNCTIONS_LIST*)(PATCH_RAM_JUMP_TABLE_ADDR))->func_name != NULL) { \
            ((PATCH_ST_FUNCTIONS_LIST*)(PATCH_RAM_JUMP_TABLE_ADDR))->func_name(__VA_ARGS__); \
        } else {                                                   \
        }                                                            \
    } while (0)

#undef TEST_EXT

#ifdef __cplusplus
}

#endif

#endif // _PATCH_DEMO_H_

#endif // (INCLUDE_MODULE_PATCH == TEST_YES) 