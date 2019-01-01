#include <stdio.h>
#include "commons.h"

/*
** Summary:
**		Reads the program memory from file and fills the memory array.
**		If the memory file contains less then MEMORY_SIZE entries, 
**		the rest of the entries are considered zero.
** Parameters:
**		inputMemoryFilename - the name of the file containing the memory
**		memory - an array representing the memory to fill
*/
//void loadMemory(char* inputMemoryFilename, int memory[])
//{
//	FILE* inputMemoryFile = fopen(inputMemoryFilename, "r");
//	if (inputMemoryFile == NULL)
//	{
//		printf("Error opening file %s", inputMemoryFilename);
//		//exit(1);
//	}
//
//	int instruction = 0;
//	int counter = 0;
//	while (fscanf(inputMemoryFile, "%x", &instruction) == 1)
//	{
//		memory[counter] = instruction;
//		counter++;
//	}
//
//	fclose(inputMemoryFile);
//
//    int i;
//    int counter = 0;
//	if (counter < MEMORY_SIZE)
//	{
//		for (i = counter; i < MEMORY_SIZE; i++)
//		{
//			memory[i] = 0;
//		}
//	}
//}