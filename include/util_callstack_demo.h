// -----------------------------------------------------------------------------
// file name: util_callstack_demo.h
// author: xuxin
// DATE:2025-02-05
// -----------------------------------------------------------------------------
   
#if (INCLUDE_MODULE_UTIL_CALLSTACK == TEST_YES) 

#ifndef _UTIL_CALLSTACK_DEMO_H_
#define _UTIL_CALLSTACK_DEMO_H_

#define UTIL_CALLSTACK_MAX_CALL_DEPTH 5
#define UTIL_CALLSTACK_MAX_SCAN_DEPTH 1000
#define UTIL_CALLSTACK_IMAGE_STR_LEN 64 // length of file name , for symbol

// os
#define UTIL_CALLSTACK_OS_LINUX TEST_NO
#define UTIL_CALLSTACK_OS_VXWORKS TEST_YES

// cpu arch
#define UTIL_CALLSTACK_CPU_ARM_CORTEX_M TEST_YES
#define UTIL_CALLSTACK_CPU_ARM_CORTEX_R TEST_NO
#define UTIL_CALLSTACK_CPU_ARM_CORTEX_A TEST_NO

#if (UTIL_CALLSTACK_CPU_ARM_CORTEX_M == TEST_YES)
typedef struct StackFrame{
    uint32_t R0;
    uint32_t R1;
    uint32_t R2;
    uint32_t R3;
    uint32_t R12;
    uint32_t LR;
    uint32_t PC;
    uint32_t xPSR;
} UTIL_CALLSTACK_ST_STACK_FRAME;

#elif  (UTIL_CALLSTACK_CPU_ARM_CORTEX_R == TEST_YES)

#elif (UTIL_CALLSTACK_CPU_ARM_CORTEX_A == TEST_YES)

#endif

typedef struct tagST_UTIL_CALLSTACK_INFO
{
	uint32_t uiInstAddr;
	uint32_t uiImageOffset;
	int8_t imageFile[UTIL_CALLSTACK_IMAGE_STR_LEN];
} UTIL_CALLSTACK_INFO_ST;


#endif // _UTIL_CALLSTACK_DEMO_H_


#endif // (INCLUDE_MODULE_UTIL_CALLSTACK == TEST_YES) 