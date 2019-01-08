#ifndef COMMONS_H
#define COMMONS_H

#define FALSE = 0
#define TRUE = 1

#define NUM_OF_REGISTERS 16
#define HEX_WORD_LENGTH 8
#define MEMORY_SIZE 512

/*
** Summary:
**		Represents the execution state of the program.
** Fields:
**		pc - an integer representing the PC, which 
**			points to the instruction to be executed.
**		isHaltExecuted - true if the HALT command 
**			has been executed, false otherwise
*/
struct executionState {
	int pc;
	int isHaltExecuted;
};
typedef struct executionState ExecutionState;


/*
** Summary:
**		Represents an instruction in the program.
*/
struct instruction
{
	int opcode;
	unsigned int rd;
	int rs;
	int rt;
	int rm;
	int imm;
};
typedef struct instruction Instruction;

int registers[NUM_OF_REGISTERS];
int memory[MEMORY_SIZE];
ExecutionState executionState;
Instruction decodedInstruction;
int instructionCounter;

#endif
