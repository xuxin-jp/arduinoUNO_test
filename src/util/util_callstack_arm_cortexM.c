//-----------------------------------------------------------------------------
// file name: util_callstack_arm_cortexM.C
// author: xuxin
// DATE:2025-02-05
// description： Cortex-M/ ARM EABI
//-----------------------------------------------------------------------------
#include "config.h"
#include "util_callstack_demo.h"

#if ((INCLUDE_MODULE_UTIL_CALLSTACK == TEST_YES) && (UTIL_CALLSTACK_CPU_ARM_CORTEX_M == TEST_YES))

#define _UTIL_CALLSTACK_ARM_CORTEX_M_C_

// get msp (interrupt and privileged)
static inline uint32_t getMSP(void) 
{
    uint32_t uiMsp;
    __asm volatile ("MRS %0, MSP" : "=r" (uiMsp));
    return uiMsp;
}

// get psp (user-level tasks in unprivileged mode)
static inline uint32_t getPSP(void)
{
    uint32_t uiPsp;
    __asm volatile ("MRS %0, PSP" : "=r" (uiPsp)); 

    return uiPsp;
}

// backtrace
void util_callstack_arm_cortexM_bt(uint32_t *stackPtr)
{
    printf("Stack backtrace:\n");
    UTIL_CALLSTACK_ST_STACK_FRAME* pstFrame = (UTIL_CALLSTACK_ST_STACK_FRAME*)stackPtr;

    for (int depth = 0; depth < UTIL_CALLSTACK_MAX_CALL_DEPTH; depth++)
    {
        if (pstFrame != NULL) 
        {
            printf("R0: %lx, R1: %lx, R2: %lx, R3: %lx, R12: %lx, LR: %lx, PC: %lx, xPSR: %lx\n",
                pstFrame->R0, pstFrame->R1, pstFrame->R2, pstFrame->R3, pstFrame->R12, pstFrame->LR, pstFrame->PC, pstFrame->xPSR);

            if (pstFrame->LR != 0) // todo lr valid / MSP OR PSP の　範囲内
            { 
                pstFrame = (UTIL_CALLSTACK_ST_STACK_FRAME *)pstFrame->LR; 
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
}

#endif
