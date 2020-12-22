#include <stdio.h>
#include <stdint.h>
#include <sys/time.h>
#include <stdlib.h>
#include "colors.h"

#ifndef CC_DIASSEMBLER_H
#define CC_DIASSEMBLER_H
	#define DISASSEMBLER_VERSION "V1.0.2"

	// returns the current timestamp in ms
	int64_t timeInMilliseconds();

	// returns the width of a CCVM opcode
	// (how many bytes an instruction takes including the opcode)
	int8_t getOpcodeWidth(int8_t opcode);

	// prints a register by looking at a byte into a bytecode buffer
	// at a specific index
	void printRegister(uint8_t* buffer, int index);

	// prints a register by looking at 4 neighbooring bytes into a bytecode buffer
	// at a specific index
	void printLiteral(uint8_t* buffer, int index);

	// looks at a specific index in a bytecode buffer and then
	// prints the entire instruction with arguments
	uint8_t printDisassembly(uint8_t* buffer, int index);

	// reads a file and returns a buffer contianing the contents
	char* readFile(char* fileName, uint32_t* fileSize);

	// prints the header above the disassembly table
	void printHeader();
#endif