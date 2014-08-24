#include <stdio.h>

#include "global.h"

#include "bmp.h"

int main() {
	bmp_file image;

	image.path="./img/simple.bmp";

	if(bmp_open(&image) == 1)
		return 1;
	if(bmp_read_header(&image) == 1) {
		bmp_close(&image);
		return 1;
	}

	bmp_close(&image);

	return 0;
}

