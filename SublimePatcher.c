#include <stdio.h>
#include <stdlib.h>

// This is the entire code lol

int main() {
	const char *filename = "sublime_text.exe";
	FILE *file = fopen(filename, "rb+");
	if (!file) {
		perror("no file");
		puts("Press Enter to exit...");
		getchar();
		return 1;
	}

	long offset = 0xa9458;
	unsigned char patch[] = {
		0x48, 0x83, 0xc4, 0x20, // ADD RSP,0x20
		0x5e,                   // POP RSI
		0xc3                    // RET
	};

	if (fseek(file, offset, SEEK_SET) != 0) {
		perror("cant find offset");
		fclose(file);
		puts("Press Enter to exit...");
		getchar();
		return 1;
		

	size_t bytes_written = fwrite(patch, sizeof(unsigned char), sizeof(patch), file);
	if (bytes_written != sizeof(patch)) {
		perror("patch failed");
		fclose(file);
		puts("Press Enter to exit...");
		getchar();
		return 1;
	}

	fclose(file);
	printf("patch complete\n");
	puts("Press Enter to exit...");
	getchar();
	return 0;
}