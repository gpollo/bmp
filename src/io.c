#include "io.h"

int readin_buffer(FILE *file, unsigned char *buffer, int size) {
	int i;

	for(i=0; i<size; i++) {
		buffer[i] = fgetc(file);
/*		printf("%c\n", buffer[i]); */
	}

    return 0;
}

