#include <stdio.h>
#include <string.h>
#include "commons.h"
#include "instruction_executer.h"
#include "lcd.h"
#include "swt.h"
#include "io_registers_handler.h"
#include "buttonStateHandler.h"

#define STOPPER_INPUT_MEMORY_SIZE 130
#define FIB_INPUT_MEMORY_SIZE 256

char* stopperInputMemory[STOPPER_INPUT_MEMORY_SIZE] = 
{
    "0D000200",
    "90000001",
    "90000004",
    "87000002",
    "09000014",
    "8B000000",
    "88000003",
    "86000000",
    "166B0000",
    "7069400F",
    "83000002",
    "7073104D",
    "82000003",
    "70823067",
    "70000007",
    "1DD00001",
    "D7D00000",
    "8B000000",
    "8A000004",
    "04A00000",
    "07000009",
    "03000050",
    "26470009",
    "70671022",
    "26430050",
    "7063102A",
    "51400008",
    "26170009",
    "70671032",
    "26130050",
    "7063103A",
    "C7D00000",
    "0DD00001",
    "70000007",
    "07000000",
    "27770000",
    "0AA00001",
    "9A000004",
    "87000002",
    "C7D00000",
    "0DD00001",
    "70000007",
    "07000000",
    "24AA0FF0",
    "0A400010",
    "9A000004",
    "87000002",
    "C7D00000",
    "0DD00001",
    "70000007",
    "07000000",
    "24AA0F00",
    "0A400100",
    "9A000004",
    "87000002",
    "C7D00000",
    "0DD00001",
    "70000007",
    "8A000004",
    "04A00000",
    "07000005",
    "5440000C",
    "21470005",
    "70170047",
    "04400001",
    "4A40000C",
    "9A000004",
    "87000002",
    "C7D00000",
    "0DD00001",
    "70000007",
    "90000004",
    "8A000004",
    "83000002",
    "81000002",
    "87000002",
    "70000007",
    "87000002",
    "83000001",
    "03300001",
    "93000001",
    "70000052",
    "83000003",
    "70831060",
    "0300009B",
    "84000000",
    "14460000",
    "7043206B",
    "83000002",
    "7073105B",
    "70000052",
    "87000002",
    "83000001",
    "23300FF0",
    "93000001",
    "70000007",
    "88000003",
    "82000003",
    "88000003",
    "82000003",
    "90000004",
    "8A000004",
    "70000052",
    "88000003",
    "88000003",
    "02800000",
    "70000047",
    "86000000",
    "83000001",
    "23330001",
    "70300070",
    "70000074",
    "83000001",
    "03300001",
    "93000001",
    "70000052",
    "83000001",
    "23300FF0",
    "93000001",
    "70000052",
    "10000000",
    "10000000",
    "81000002",
    "8B000000",
    "90000001",
    "90000001",
    "83000002",
    "81000002",
    "87000002",
    "70000007"
};

char* fibonachiInputMemory[FIB_INPUT_MEMORY_SIZE] = 
{
    "0D000200",
    "C3000100",
    "B0000005",
    "D2000101",
    "F0000000",
    "1DD00003",
    "D9D00002",
    "DFD00001",
    "D3D00000",
    "06000001",
    "7036200E",
    "02300000",
    "0DD00003",
    "EF000000",
    "13300001",
    "B0000005",
    "09200000",
    "C3D00000",
    "13300002",
    "B0000005",
    "02290000",
    "C3D00000",
    "CFD00001",
    "C9D00002",
    "0DD00003",
    "EF000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000007"
};

/*
** Summary:
**		Decodes an instruction.
**		Each instruction is decoded using a mask to extract the bits of each component.
**		Each component of the instruction is then assigned to the appropriate field in
**		the decodedInstruction struct.
** Parameters:
**		instructionToDecode - an integer representing the instruction from memory to decode
**		decodedInstruction - a struct representing the decoded instruction
*/
void decodeInstruction(int instructionToDecode, Instruction* decodedInstruction)
{
	int immMask = 0x00000fff;
	int mask = 0xf;

	decodedInstruction->imm = instructionToDecode & immMask;
	decodedInstruction->rm = (instructionToDecode >> 12) & mask;
	decodedInstruction->rt = (instructionToDecode >> 16) & mask;
	decodedInstruction->rs = (instructionToDecode >> 20) & mask;
	decodedInstruction->rd = (instructionToDecode >> 24) & mask;
	decodedInstruction->opcode = (instructionToDecode >> 28) & mask;
}

void loadFibonachi()
{
	int instruction;
    int i;
    char temp;
    
    instruction = 0;
    for (i = 0; i < MEMORY_SIZE; i++) 
    {
        if (i <= FIB_INPUT_MEMORY_SIZE)
        {
            instruction = (long)strtoul(fibonachiInputMemory[i], NULL, 16);
            memory[i] = instruction;
        }
        else
        {
            memory[i] = 0;
        }
    }
}

void loadStopper()
{
    int instruction;
    int i;

    instruction = 0;
    for (i = 0; i < MEMORY_SIZE; i++) 
    {
        if (i <= STOPPER_INPUT_MEMORY_SIZE) 
        {
            instruction = (long) strtoul(stopperInputMemory[i], NULL, 16);
            memory[i] = instruction;
        }
        else
        {
            memory[i] = 0;
        }
    }
}

void display(int instruction, int pc)
{
    char instructionString[HEX_WORD_LENGTH + 1];
    char pcString[4];
    
    sprintf(instructionString, "%08X", instruction);
    LCD_WriteStringAtPos(instructionString, 0, 0);
    sprintf(pcString, "%03X", pc);
    LCD_WriteStringAtPos(pcString, 1, 0);
}

void loadProgram()
{
    if (SWT_GetValue(7)) 
    {
        loadStopper();
    }
    else
    {
        loadFibonachi();
    }
}

void initSimulator()
{
    int i;
	for (i = 0; i < NUM_OF_REGISTERS; i++)
	{
		registers[i] = 0;
	}
    
    for (i = 0; i < NUM_OF_IO_REGISTERS; i++) 
    {
        IORegisters[i] = 0;
    }

	loadProgram();
	
	executionState.pc = 0;
	executionState.isHaltExecuted = 0;

	instructionCounter = 0;
}

void setPauseState()
{
    if (btnState.BTNL)
    {
        btnState.BTNL = 0;
        executionState.isPause = !executionState.isPause;
    }
}

void execute()
{
    SWT_refreshAll();
    getLcdState();
    
    if (!executionState.isHaltExecuted) 
    {
        setPauseState();
        if(!executionState.isPause)       
        {
            decodeInstruction(memory[executionState.pc], &decodedInstruction);
            executeInstruction(&decodedInstruction, memory, registers, &executionState);
            instructionCounter++;
        }
        else
        {
            if(btnState.BTNR)
            {
                btnState.BTNR = 0;
                decodeInstruction(memory[executionState.pc], &decodedInstruction);
                executeInstruction(&decodedInstruction, memory, registers, &executionState);
                instructionCounter++;
            }
        }
    }
    
    
}