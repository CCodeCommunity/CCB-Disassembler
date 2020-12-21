#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

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

void printDisassembly(uint8_t* buffer, int index) {
	#if defined(__APPLE__) || defined(__linux__)
		char* red = KRED;
		char* green = KGRN;
		char* magenta = KMAG;
		char* yellow = KYEL;
		char* blue = KBLU;
		char* norm = KNRM;
	#else
		char* red = "";
		char* green = "";
		char* magenta = "";
		char* yellow = "";
		char* blue = "";
		char* norm = "";
	#endif

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
		printf("%s???%s", red, red);
	}
}

int main(int argc, char* argv[]) {
	if (argc >= 2) {
		#if defined(__APPLE__) || defined(__linux__)
			char* red = KRED;
			char* green = KGRN;
			char* magenta = KMAG;
			char* yellow = KYEL;
			char* blue = KBLU;
			char* norm = KNRM;
		#else
			char* red = "";
			char* green = "";
			char* magenta = "";
			char* yellow = "";
			char* blue = "";
			char* norm = "";
		#endif

		// open file
		FILE* fileptr = fopen(argv[1], "rb");
		
		// determain file size
		fseek(fileptr, 0, SEEK_END);
		int32_t fileLen = ftell(fileptr);
		rewind(fileptr);

		// load file into bugger
		uint8_t* buffer = (uint8_t*)malloc(fileLen * sizeof(int8_t));
		fread(buffer, fileLen, 1, fileptr);

		// close file
		fclose(fileptr);

		int i = 0;

		// skip past the buffer
		while (buffer[i] != 0x1d || buffer[i + 1] != 0x1d || buffer[i + 2] != 0x1d || buffer[i + 3] != 0x1d) {
			++i;
		}

		int headerSize = i;
		int opcodeCount = 0;

		printf("%scode disassembly:%s\n", green, norm);

		i += 4;

		while (i < fileLen) {
			++opcodeCount;
			printf("%s%08X%s │ ", red, i, norm);

			int start = i;

			int8_t width = getOpcodeWidth(buffer[i]);

			printf("%s", yellow);
			for (int j = 0; j < width; j++)
				printf("%02x ", (uint8_t)buffer[i++]);
			printf("%s", norm);


			for (int j = 0; j < (9 - width); j++)
				printf("   ");

			printf("│ ");

			printf("%s", magenta);
			printDisassembly(buffer, start);
			printf("%s", norm);

			puts("");
		}

		printf("\n%sinfo:%s\n", green, norm);
		printf("%sheader size:%s          %d bytes\n", red, yellow, headerSize);
		printf("%sopcode count:%s         %d opcodes\n", red, yellow, opcodeCount);
		printf("%sdisassembler version:%s V1.0.1\n", red, yellow);
		printf("%s", norm);
	} else {
		puts("CC Disassembler V1.0.1");
	}
}