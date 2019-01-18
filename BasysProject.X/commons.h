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
struct t_executionState {
    int isPause;
    int lcdState;
	int pc;
	int isHaltExecuted;
    int memAdress4lcd;
};
typedef struct t_executionState ExecutionState;

struct swtState {
    int SW0;
    int SW1;
    int SW2;
    int SW3;
    int SW4;
    int SW5;
    int SW6;
    int SW7;  
};
typedef struct swtState SwtState;


struct btnState {

    int prevBTNU;
    int BTNU;
    int BTND;
    int BTNC;
    int prevBTNL;
    int BTNL;
    int prevBTNR;
    int BTNR;
};
typedef struct btnState BtnState;





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
BtnState btnState;
Instruction decodedInstruction;
int instructionCounter;
SwtState swtState;

#endif
