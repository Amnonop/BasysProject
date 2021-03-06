#include "commons.h"
#include "instruction_executer.h"
#include "io_registers_handler.h"

enum Opcodes
{
	Add = 0,
	Sub = 1,
	And = 2,
	Or = 3,
	Sll = 4,
	Sra = 5,
	Mac = 6,
	Branch = 7,
    In = 8,
    Out = 9,
	Jal = 11,
	Lw = 12,
	Sw = 13,
	Jr = 14,
	Halt = 15
};

int signExtend(int number)
{
	return (((number & 0x800) == 0x800) ? (0xFFFFF000 | number) : number);
}

void add(Instruction* instruction, int registers[], ExecutionState* state)
{
	registers[instruction->rd] = registers[instruction->rs] + registers[instruction->rt] + signExtend(instruction->imm);
	state->pc++;
}

void sub(Instruction* instruction, int registers[], ExecutionState* state)
{
	registers[instruction->rd] = registers[instruction->rs] - registers[instruction->rt] - signExtend(instruction->imm);
	state->pc++;
}

void and(Instruction* instruction, int registers[], ExecutionState* state)
{
	registers[instruction->rd] = registers[instruction->rs] & registers[instruction->rt] & signExtend(instruction->imm);
	state->pc++;
}

void or(Instruction* instruction, int registers[], ExecutionState* state)
{
	registers[instruction->rd] = registers[instruction->rs] | registers[instruction->rt] | signExtend(instruction->imm);
	state->pc++;
}

void sll(Instruction* instruction, int registers[], ExecutionState* state)
{
	registers[instruction->rd] = registers[instruction->rs] << (registers[instruction->rt] + instruction->imm);
	state->pc++;
}

void sra(Instruction* instruction, int registers[], ExecutionState* state)
{
	registers[instruction->rd] = registers[instruction->rs] >> (registers[instruction->rt] + instruction->imm);
	state->pc++;
}

void mac(Instruction* instruction, int registers[], ExecutionState* state)
{
	registers[instruction->rd] = registers[instruction->rs] * registers[instruction->rt] + registers[instruction->rm] + signExtend(instruction->imm);
	state->pc++;
}

void branch(Instruction* instruction, int registers[], ExecutionState* state)
{
	int rmValue = instruction->rm;
	int rsRegisterValue = registers[instruction->rs];
	int rtRegisterValue = registers[instruction->rt];
	if ((rmValue == 0 && (rsRegisterValue == rtRegisterValue)) ||
		(rmValue == 1 && (rsRegisterValue != rtRegisterValue)) ||
		(rmValue == 2 && (rsRegisterValue > rtRegisterValue)) ||
		(rmValue == 3 && (rsRegisterValue < rtRegisterValue)) ||
		(rmValue == 4 && (rsRegisterValue >= rtRegisterValue)) ||
		(rmValue == 5 && (rsRegisterValue <= rtRegisterValue)))
	{
		state->pc = instruction->imm;
	}
	else
	{
		state->pc++;
	}
}

void in(Instruction* instruction, ExecutionState* state)
{
    int ioRegisterIndex;
    ioRegisterIndex = registers[instruction->rs] + signExtend(instruction->imm);
    registers[instruction->rd] = IORegisters[ioRegisterIndex];
    state->pc++;
}

void out(Instruction* instruction, ExecutionState* state)
{
    int writeIndex = registers[instruction->rs] + signExtend(instruction->imm);
    setIORegister(writeIndex, registers[instruction->rd]);
    state->pc++;
}

void jumpAndLink(Instruction* instruction, int registers[], ExecutionState* state)
{
	registers[15] = (state->pc + 1) & 0xfff;
	state->pc = instruction->imm;
}

void loadWord(Instruction* instruction, int memory[], int registers[], ExecutionState* state)
{
	int memoryAddress = (registers[instruction->rs] + signExtend(instruction->imm)) & 0xfff;
	registers[instruction->rd] = memory[memoryAddress];
	state->pc++;
}

void saveWord(Instruction* instruction, int memory[], int registers[], ExecutionState* state)
{
	int memoryAddress = (registers[instruction->rs] + signExtend(instruction->imm)) & 0xfff;
	memory[memoryAddress] = registers[instruction->rd];
	state->pc++;
}

void jr(Instruction* instruction, int registers[], ExecutionState* state)
{
	state->pc = registers[instruction->rd] & 0xfff;
}

/*
** Summary:
**		Executes the instruction according to the opcode.
** Parameters:
**		instruction - an Instruction struct containing the instruction to execute
**		memory - an array representing the memory of the program
**		registers - an array representing the registers of the program
**		state - an ExecutionState struct containing the state of the program execution
*/
void executeInstruction(Instruction* instruction, int memory[], int registers[], ExecutionState* state)
{
	switch (instruction->opcode)
	{
		case Add:
			add(instruction, registers, state);
			break;
		case Sub:
			sub(instruction, registers, state);
			break;
		case And:
			and(instruction, registers, state);
			break;
		case Or:
			or(instruction, registers, state);
			break;
		case Sll:
			sll(instruction, registers, state);
			break;
		case Sra:
			sra(instruction, registers, state);
			break;
		case Mac:
			mac(instruction, registers, state);
			break;
		case Branch:
			branch(instruction, registers, state);
			break;
        case In:
            in(instruction, state);
            break;
        case Out:
            out(instruction, state);
            break;
		case Jal:
			jumpAndLink(instruction, registers, state);
			break;
		case Lw:
			loadWord(instruction, memory, registers, state);
			break;
		case Sw:
			saveWord(instruction, memory, registers, state);
			break;
		case Jr:
			jr(instruction, registers, state);
			break;
		case Halt:
			state->isHaltExecuted = 1;
			break;
		default:
			break;
	}
}