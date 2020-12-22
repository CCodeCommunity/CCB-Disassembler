#include "ccd.h"

int64_t timeInMilliseconds() {
    struct timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);
    return ((int64_t) time.tv_sec) * 1000 + ((int64_t) time.tv_nsec) / 1000000;
}

int8_t getOpcodeWidth(int8_t opcode) {
	if (opcode == 0x07 || opcode == 0x0b)
		return 9;
	else if (opcode == 0x06 || opcode == 0x08 || opcode == 0x09 || opcode == 0x31)
		return 6;
	else if (opcode == 0x01 || opcode == 0x04 || opcode == 0x0c || opcode == 0x20 || opcode == 0x32 || opcode == 0x60 || opcode == 0x33 || opcode == 0x34 || opcode == 0x35 || opcode == 0x36 || opcode == 0x37)
		return 5;
	else if (opcode == 0x0a || opcode == 0x10 || opcode == 0x12 || opcode == 0x14 || opcode == 0x16 || opcode == 0x1a || opcode == 0x1c || opcode == 0x1e || opcode == 0x30)
		return 3;
	else if (opcode == 0x02 || opcode == 0x03 || opcode == 0x18 || opcode == 0x50 || opcode == 0x51)
		return 2;
	else
		return 1;
}

void printRegister(uint8_t* buffer, int index) {
	printf("%c", (buffer[index] % 4) + 97);
}

void printLiteral(uint8_t* buffer, int index) {
	printf("%d", ((buffer[index]) << 24) | ((buffer[index + 1]) << 16) | ((buffer[index + 2]) << 8) | (buffer[index + 3]));
}

char* readFile(char* fileName, uint32_t* fileSize) {
	// open file
	FILE* fileptr = fopen(fileName, "rb");
	
	// determain file size
	fseek(fileptr, 0, SEEK_END);
	*fileSize = ftell(fileptr);
	rewind(fileptr);

	// load file into bugger
	uint8_t* buffer = (uint8_t*)malloc(*fileSize * sizeof(int8_t));
	fread(buffer, *fileSize, 1, fileptr);

	// close file
	fclose(fileptr);

	return buffer;
}

void printHeader() {
	printf("%scode disassembly:%s\n", GREEN, NORM);
	printf("address  | bytes                      | Disassembly\n");
	printf("---------------------------------------------------\n");
}

uint8_t printDisassembly(uint8_t* buffer, int index) {
	uint8_t oc = buffer[index]; // OpCode

	if (oc == 0x00) {
		printf("stp");
	} else if (oc == 0x01) {
		printf("psh ");
		printLiteral(buffer, index + 1);
	} else if (oc == 0x02) {
		printf("psh ");
		printRegister(buffer, index + 1);
	} else if (oc == 0x03) {
		printf("pop ");
		printRegister(buffer, index + 1);
	} else if (oc == 0x04) {
		printf("pop &");
		printLiteral(buffer, index + 1);
	} else if (oc == 0x05) {
		printf("dup");
	} else if (oc == 0x06) {
		printf("mov ");
		printRegister(buffer, index + 1);
		printf(", ");
		printLiteral(buffer, index + 2);
	} else if (oc == 0x07) {
		printf("mov &");
		printLiteral(buffer, index + 1);
		printf(", ");
		printLiteral(buffer, index + 5);
	} else if (oc == 0x08) {
		printf("mov ");
		printRegister(buffer, index + 1);
		printf(", &");
		printLiteral(buffer, index + 2);
	} else if (oc == 0x09) {
		printf("mov &");
		printLiteral(buffer, index + 1);
		printf(", ");
		printRegister(buffer, index + 5);
	} else if (oc == 0x10) {
		printf("add ");
		printRegister(buffer, index + 1);
		printf(", ");
		printRegister(buffer, index + 2);
	} else if (oc == 0x11) {
		printf("add");
	} else if (oc == 0x12) {
		printf("sub ");
		printRegister(buffer, index + 1);
		printf(", ");
		printRegister(buffer, index + 2);
	} else if (oc == 0x13) {
		printf("sub");
	} else if (oc == 0x14) {
		printf("mul ");
		printRegister(buffer, index + 1);
		printf(", ");
		printRegister(buffer, index + 2);
	} else if (oc == 0x15) {
		printf("mul");
	} else if (oc == 0x16) {
		printf("div ");
		printRegister(buffer, index + 1);
		printf(", ");
		printRegister(buffer, index + 2);
	} else if (oc == 0x17) {
		printf("div");
	} else if (oc == 0x18) {
		printf("not ");
		printRegister(buffer, index + 1);
	} else if (oc == 0x19) {
		printf("not");
	} else if (oc == 0x1a) {
		printf("and ");
		printRegister(buffer, index + 1);
		printf(", ");
		printRegister(buffer, index + 2);
	} else if (oc == 0x1b) {
		printf("and");
	} else if (oc == 0x1c) {
		printf("or ");
		printRegister(buffer, index + 1);
		printf(", ");
		printRegister(buffer, index + 2);
	} else if (oc == 0x1d) {
		printf("or");
	} else if (oc == 0x1e) {
		printf("xor ");
		printRegister(buffer, index + 1);
		printf(", ");
		printRegister(buffer, index + 2);
	} else if (oc == 0x1f) {
		printf("xor");
	} else if (oc == 0x20) {
		printf("jmp ");
		printLiteral(buffer, index + 1);
	} else if (oc == 0x30) {
		printf("cmp ");
		printRegister(buffer, index + 1);
		printf(", ");
		printRegister(buffer, index + 2);
	} else if (oc == 0x31) {
		printf("cmp ");
		printRegister(buffer, index + 1);
		printf(", ");
		printLiteral(buffer, index + 2);
	} else if (oc == 0x32) {
		printf("cmp ");
		printLiteral(buffer, index + 1);
	} else if (oc == 0x33) {
		printf("je ");
		printLiteral(buffer, index + 1);
	} else if (oc == 0x34) {
		printf("jne ");
		printLiteral(buffer, index + 1);
	} else if (oc == 0x35) {
		printf("jg ");
		printLiteral(buffer, index + 1);
	} else if (oc == 0x36) {
		printf("js ");
		printLiteral(buffer, index + 1);
	} else if (oc == 0x37) {
		printf("jo ");
		printLiteral(buffer, index + 1);
	} else if (oc == 0x40) {
		printf("frs");
	} else if (oc == 0x50) {
		printf("inc ");
		printRegister(buffer, index + 1);
	} else if (oc == 0x51) {
		printf("dec ");
		printRegister(buffer, index + 1);
	} else if (oc == 0x52) {
		printf("inc");
	} else if (oc == 0x53) {
		printf("dec");
	} else if (oc == 0x60) {
		printf("call ");
		printLiteral(buffer, index + 1);
	} else if (oc == 0x61) {
		printf("ret");
	} else if (oc == 0xff) {
		printf("syscall");
	} else {
		printf("%s??? (unknown instruction)%s", RED, RED);
		return 1;
	}

	return 0;
}