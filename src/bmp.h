#ifndef BMP_H
#define BMP_H

#include <stdio.h>
#include <stdlib.h> 

#include "global.h"
#include "io.h"

typedef struct bmp_file {
	unsigned char buffer[BUFFER_SIZE];
	unsigned char *data;

	char *path;
	int size_file;
	int offset;
	int size_DIB;
	int width;
	int height;
	int bPP;
	int BPP;
	int size_image;

	FILE *file;
} bmp_file;

int bmp_open(bmp_file *bmp, char *perm);
int bmp_close(bmp_file *bmp);
int bmp_read_header(bmp_file *bmp);
int bmp_read_image(bmp_file *bmp);
int bmp_dump_header(bmp_file *bmp, unsigned char *buffer);
int bmp_write_image(bmp_file *bmp, unsigned char *buffer, int size);
int bmp_check_size(bmp_file *bmp);
int bmp_free(bmp_file *bmp);

#endif
