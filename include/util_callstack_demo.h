//-----------------------------------------------------------------------------
// file name: util_callstack_demo.h
// author: xuxin
// DATE:2025-02-05
//-----------------------------------------------------------------------------
   
#if (INCLUDE_MODULE_UTIL_CALLSTACK == TEST_YES) 

#ifndef _UTIL_CALLSTACK_DEMO_H_
#define _UTIL_CALLSTACK_DEMO_H_

#define UTIL_CALLSTACK_MAX_DEPTH 5
#define UTIL_CALLSTACK_IMAGE_STR_LEN 64 //length of file name 

#define UTIL_CALLSTACK_OS_LINUX TEST_NO
#define UTIL_CALLSTACK_OS_VXWORKS TEST_YES

#define UTIL_CALLSTACK_CPU_ARM_CORTEX_M TEST_YES
#define UTIL_CALLSTACK_CPU_ARM_CORTEX_R TEST_NO
#define UTIL_CALLSTACK_CPU_ARM_CORTEX_A TEST_NO

typedef struct tagST_UTIL_CALLSTACK_INFO
{
	uint32_t uiInstAddr;
	uint32_t uiImageOffset;
	int8_t imageFile[UTIL_CALLSTACK_IMAGE_STR_LEN];
} UTIL_CALLSTACK_INFO_ST;


#endif // _UTIL_CALLSTACK_DEMO_H_


#endif // (INCLUDE_MODULE_UTIL_CALLSTACK == TEST_YES) 