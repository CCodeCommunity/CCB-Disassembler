// gcc main.c ccd.c -o ccd -O3
#include <stdio.h>
#include <stdlib.h>

#include "ccd.h"

int main(int argc, char* argv[]) {
	if (argc >= 2) {
		double start = ((double)timeInMilliseconds()) / 1000;

		int32_t fileLen;
		uint8_t* buffer = readFile(argv[1], &fileLen);

		int i = 0;

		// skip past the buffer
		while (buffer[i] != 0x1d || buffer[i + 1] != 0x1d || buffer[i + 2] != 0x1d || buffer[i + 3] != 0x1d)
			++i;

		int headerSize = i;
		int opcodeCount = 0;

		uint8_t encounteredError = 0;

		printHeader();

		i += 4;

		while (i < fileLen) {
			++opcodeCount;
			printf("%s%08X%s | ", RED, i, NORM);

			int start = i;

			int8_t width = getOpcodeWidth(buffer[i]);

			printf("%s", YELLOW);
			for (int j = 0; j < width; j++)
				printf("%02x ", (uint8_t)buffer[i++]);
			printf("%s", NORM);

			for (int j = 0; j < (9 - width); j++)
				printf("   ");

			printf("| ");

			printf("%s", encounteredError ? RED : MAGENTA);
			uint8_t error = printDisassembly(buffer, start);

			if (error) {
				encounteredError = 1;
			}

			printf("%s", NORM);

			puts("");
		}

		printf("\n%sinfo:%s\n", GREEN, NORM);
		printf("%sheader size:%s           %d bytes\n", RED, YELLOW, headerSize);
		printf("%sopcode count:%s          %d opcodes\n", RED, YELLOW, opcodeCount);
		printf("%stotal ccb size:%s        %d bytes\n", RED, YELLOW, fileLen);

		double end = ((double)timeInMilliseconds()) / 1000;
		printf("%sdisassembly time:%s      %.3f seconds\n", RED, YELLOW, end - start);
		printf("%sdisassembler version:%s  %s\n", RED, YELLOW, DISASSEMBLER_VERSION);
		printf("%s", NORM);
	} else {
		printf("CC Disassembler %s", DISASSEMBLER_VERSION);
	}
}