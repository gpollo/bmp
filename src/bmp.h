#include <stdio.h>

#include "global.h"

typedef struct bmp_file {
	unsigned char buffer[BUFFER_SIZE];
	char *path;
	int size_file;
	int size_DIB;
	int offset;

	FILE *file;
} bmp_file;

int bmp_open(bmp_file *bmp);
int bmp_close(bmp_file *bmp);
int bmp_read_header(bmp_file *bmp);
