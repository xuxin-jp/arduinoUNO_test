//-----------------------------------------------------------------------------
// file name: util_transactional_singleThread.C
// author: xuxin
// DATE:2025-02-05
// description： transactional operation
//-----------------------------------------------------------------------------
#include "config.h"

#if (INCLUDE_MODULE_UTIL_TRANSACTIONAL == TEST_YES)
#include <setjmp.h>

#define _UTIL_TRANSACTIONAL_SINGLE_THREAD_C_


jmp_buf env;  // buffer

void util_transactional_riskyOperation(int errorcode) 
{
    if (errorcode)
    {
        printf("An error occurred! Jumping back to safe state.\n");
        longjmp(env, 1);  // roll back to saved state(setjmp) with return value 1
    }
    printnf("Operation successful");
}

// transaction operation
void util_transactional_demo(void)
{
    if (setjmp(env) == 0) // first time call setjmp，return 0
    {
        printnf("risky operation...");
        risky_operation(1);  // an exception
    }
    else
    {
        // After longjmp: setjmp returns 1
        printf("Recovered. Continuing execution.\n");
    }

    printf("Program continues normally.\n");
}

#endif