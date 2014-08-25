#include "io.h"

int readin_buffer(FILE *file, unsigned char *buffer, int size) {
	int i;

	for(i=0; i<size; i++) {
		buffer[i] = fgetc(file);
	}

    return 0;
}

int writeout_buffer(FILE *file, unsigned char *buffer, int size) {
	int i;

	for(i=0; i<size; i++) {
		fputc(buffer[i], file);
	}

    return 0;
}

