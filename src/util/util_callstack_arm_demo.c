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
#define CALLSTACK_INS_SP_PUSH_MASK 0xFFFF0000
#define CALLSTACK_INS_SP_OPERATION_MASK 0xFFFFF000
#define CALLSTACK_INS_SP_OFFSET_MASK    0x00000FFF

#define CALLSTACK_INS_SP_OPERATION_PUSH_NULL 0xE92D0000 // push {}
#define CALLSTACK_INS_SP_OPERATION_ADD_0 0xE28DD000 // ADD SP, SP, #0
#define CALLSTACK_INS_SP_OPERATION_PUSH_LR 0xE52DE000 // STR LR, [SP, #-0]! == push  {LR}


#define CALLSTACK_INS_SP_STMDB_SP_MASK		0xffffc000
#define CALLSTACK_INS_SP_FP_MASK			0x00000800
#define CALLSTACK_INS_SP_VALUE_MASK			0x000000ff
#define CALLSTACK_INS_SP_ROTATION_MASK		0x00000f00
#define CALLSTACK_INS_SP_MULEQ_SP_MASK		0xffff00f0
#define CALLSTACK_INS_SP_POP_LR_MASK		0xffffc000
#define CALLSTACK_INS_SP_POP_REG_MASK		0xffffc000

#define CALLSTACK_INS_SP_STDDB_SP_LR_INSTR	0xe92d4000
#define CALLSTACK_INS_SP_STDDB_SP_R12_LR_INSTR	0xe92dc000
#define CALLSTACK_INS_SP_STDDB_SP_INSTR		0xe92d0000
#define CALLSTACK_INS_SP_SUB_SP_SP_IMM_INSTR 0xe24dd000
#define CALLSTACK_INS_SP_STR_LR_SP_INSTR		0xe52de004
#define CALLSTACK_INS_SP_SUB_SP_SP_IP_INSTR	0xe04dd00c
#define CALLSTACK_INS_SP_MOV_IP_IMM_INSTR	0xe3a0c000
#define CALLSTACK_INS_SP_LDR_IP_PC_IMM_INSTR 0xe59fc000
#define CALLSTACK_INS_SP_MULEQ_SP_INSTR		0x000d0090
#define CALLSTACK_INS_SP_POP_LR_INSTR		0xe8bd4000
#define CALLSTACK_INS_SP_POP_REG_INSTR		0xe8bd0000
#define CALLSTACK_INS_SP_STMFD_SP_INSTR 0xe8bd8000 // (STMFD sp!, {lr})
#define CALLSTACK_INS_SP_LDR_SP_INSTR   0xe49df004 // (LDR sp, [sp, #-4]!)

// The lower 12 bits represent a register bitmap,
// with each bit indicating whether the corresponding register is involved 
// (1 means involved, 0 means not involved).
static int32_t count_registers(int offset) 
{
    static const int8_t sregCountTable[16] = {
        0,  // 0x0 = 0000 → 0 reg
        1,  // 0x1 
        1,  // 0x2 
        2,  // 0x3 
        1,  // 0x4 
        2,  // 0x5 
        2,  // 0x6 
        3,  // 0x7 
        1,  // 0x8 
        2,  // 0x9 
        2,  // 0xA 
        3,  // 0xB 
        2,  // 0xC 
        3,  // 0xD 
        3,  // 0xE 
        4   // 0xF
    };

    int count = 0;
    for (int i = 0; i < 3; i++) {
        // get the register count from the lookup table.
        count += sregCountTable[(offset >> (i * 4)) & 0xF];
    }

    return count;
}


void util_callstack_arm_cortexR_bt(uint32_t uiSp,
									 uint32_t uiRa,
									 uint32_t uiPc,
									 uint32_t *pRetaddr,
									 uint32_t uiDepth)
{
	int32_t i;
	int32_t j;
	int32_t *pInstr = uiPc;
	int32_t memAddr = 0;
	int32_t instr;
	int32_t maskinstr;
	int32_t scanCount = 0;
	int32_t numSaved;
	int32_t offset = 0;
	int32_t value;
	int32_t rotation;
	bool bFoundBxJr = false;

	if (NULL == pRetaddr)
	{
		return;
	}

	if (NULL == uiPc)
	{
		uiPc = uiRa;
	}

	memset(pRetaddr, 0, uiDepth); //depth <= UTIL_CALLSTACK_MAX_CALL_DEPTH

	for (i = 0; i < uiDepth; i++)
	{
		if (0 == i)
		{
			pInstr = uiPc;
			scanCount = 0;
			while (scanCount++ < UTIL_CALLSTACK_MAX_SCAN_DEPTH)
			{
				// todo: pInstr valid
				instr = *pInstr;
				maskinstr = instr & CALLSTACK_INS_SP_OPERATION_MASK;
				if (instr == CALLSTACK_INS_BX_LR)
				{
					bFoundBxJr = true; // found the return address
					goto callstack_done;
				}

				if ((instr & CALLSTACK_INS_SP_PUSH_MASK) == CALLSTACK_INS_SP_OPERATION_PUSH_NULL)
				{
					break;
				}

				if (maskinstr == CALLSTACK_INS_SP_OPERATION_ADD_0)
				{
					break;
				}

				if (maskinstr == CALLSTACK_INS_SP_OPERATION_PUSH_LR)
				{
					break;
				}
				++pInstr;
			}

		}

		pInstr = uiPc;
		scanCount = 0;
		
		// to scan all instructions that operate on the stack.
		while (scanCount++ < UTIL_CALLSTACK_MAX_SCAN_DEPTH)
		{
			instr = *pInstr;
			// todo : Instruction validity check
			if (instr == CALLSTACK_INS_SP_STR_LR_SP_INSTR) 
			{
				uiRa = uiSp;  // Save the return address
				offset = instr & CALLSTACK_INS_SP_OFFSET_MASK;
				uiSp += offset;

				for (j = 0; j < UTIL_CALLSTACK_MAX_SCAN_DEPTH; j++)
				{
					--pInstr;

					// todo : Instruction validity check
					instr = *pInstr;
					maskinstr = instr & CALLSTACK_INS_SP_OPERATION_MASK;
					// Termination conditions: POP or LDR instructions
					if (maskinstr == CALLSTACK_INS_SP_STMFD_SP_INSTR || instr == CALLSTACK_INS_SP_LDR_SP_INSTR) 
					{
						break;
					}

					offset = 0;  // Reset offset for each iteration

					// Handle STMDB (stack decrement store) instruction
					if ((instr & CALLSTACK_INS_SP_STMDB_SP_MASK) == CALLSTACK_INS_SP_STDDB_SP_INSTR) {
						offset = instr & CALLSTACK_INS_SP_OFFSET_MASK;
						numSaved = count_registers(offset);
						uiSp += numSaved * sizeof(int32_t);
						break;  // Exit early after processing this instruction
					}
				}
			}

			if ((instr & CALLSTACK_INS_SP_POP_LR_MASK) == CALLSTACK_INS_SP_POP_LR_INSTR) // POP {LR}
			{
				offset = instr & CALLSTACK_INS_SP_OFFSET_MASK;
				numSaved = count_registers(offset);
				uiSp = uiSp - ((numSaved + 1) * sizeof(uint32_t));
			}

			if ((instr & CALLSTACK_INS_SP_POP_REG_MASK) == CALLSTACK_INS_SP_POP_REG_INSTR)
			{
				offset = instr & CALLSTACK_INS_SP_OFFSET_MASK;
				numSaved = count_registers(offset);
				uiSp = uiSp - ((numSaved) * sizeof(uint32_t));
			}
			// todo : Here, only a subset of instructions is scanned.
			--pInstr;
		}

callstack_done:
		if (uiRa)
		{
			if (uiPc == uiRa)
			{
				return;
			}
			else
			{
				pRetaddr[i] = uiRa - 4; //
				uiPc = pRetaddr[i];
				uiRa = 0;
			}
		}
		else
		{
			break;
		}
	}
	return;
}

void util_callstack(uint32_t uiTaskID, UTIL_CALLSTACK_INFO_ST *pstStackInfo, uint16_t uiDepth)
{
	uint32_t uiSp = 0;
	uint32_t uiRa = 0;
	uint32_t uiPc = 0;
	uint32_t arRetaddr[UTIL_CALLSTACK_MAX_CALL_DEPTH];
	if (NULL == pstStackInfo)
	{
		return;
	}

	if (UTIL_CALLSTACK_MAX_CALL_DEPTH < uiDepth)
	{
		uiDepth = UTIL_CALLSTACK_MAX_CALL_DEPTH;
	}

	memset(pstStackInfo, (int)0, uiDepth * sizeof(UTIL_CALLSTACK_INFO_ST));
	{
 		REG_SET stRegs;
		(void)taskRegsGet((int)uiTaskID, &stRegs); // get sp/ra/pc registers
		uiSp = (uint32_t)stRegs.arm_sp;
		uiRa = (uint32_t)stRegs.arm_lr;
		uiPc = (uint32_t)stRegs.arm_pc; 
	}

	util_callstack_arm_cortexR_bt(uiSp, uiRa, uiPc, arRetaddr, uiDepth);

	return;
}

＃endif
