#ifndef IO_REGISTERS_HANDLER_H
#define	IO_REGISTERS_HANDLER_H

#define NUM_OF_IO_REGISTERS 5

int IORegisters[NUM_OF_IO_REGISTERS];

int isReadOnlyRegister(int registerIndex);

#endif

