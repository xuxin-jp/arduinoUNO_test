//-----------------------------------------------------------------------------
// file name: util_callstack_arm_demo.C
// author: xuxin
// DATE:2025-02-06
// description： ARM EABI 
//-----------------------------------------------------------------------------
#include "config.h"

#if (INCLUDE_MODULE_UTIL_CALLSTACK == TEST_YES) 
#include "util_callstack_demo.h"
#define _UTIL_CALLSTACK_ARM_DEMO_C_

#define CALLSTACK_INS_BX_LR 0xE12FFF1E // return instruction thumb1 arm0

// NOP / placeholder instruction，No actual impact on SP.
#define CALLSTACK_INS_SP_OPERATION_PUSH_NULL 0xE92D0000 // push {}
#define CALLSTACK_INS_SP_OPERATION_ADD_0 0xE28DD000 // ADD SP, SP, #0
#define CALLSTACK_INS_SP_OPERATION_PUSH_LR 0xE52DE000 // STR LR, [SP, #-0]! == push  {LR}

void util_callstack(uint32_t uiTaskID, UTIL_CALLSTACK_INFO_ST *pstStackInfo, uint16_t uiDepth)
{
	uint32_t uiSp = 0;
	uint32_t uiRa = 0;
	uint32_t uiPc = 0;
	
	if (NULL == pstStackInfo)
	{
		return;
	}

	if (UTIL_CALLSTACK_MAX_DEPTH < uiDepth)
	{
		uiDepth = UTIL_CALLSTACK_MAX_DEPTH;
	}

	memset(pstStackInfo, (int)0, uiDepth * sizeof(UTIL_CALLSTACK_INFO_ST));
	{
/* 		REG_SET stRegs;
		(void)taskRegsGet((int)uiTaskID, &stRegs);//get sp/ra/pc registers
		uiSp = (uint32_t)stRegs.arm_sp;
		uiRa = (uint32_t)stRegs.arm_lr;
		uiPc = (uint32_t)stRegs.arm_pc; */
	}

	// util_callBackTrace(uiSp, uiRa, uiPc, arRetaddr, ulDepth, B_TRUE, bExcp);

	return;
}

＃endif
