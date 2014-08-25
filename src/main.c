#include <stdio.h>

#include "global.h"
#include "bmp.h"
#include "algo.h"

int main(int argc, char *argv[]) {
	unsigned char *buffer;

	bmp_file image;
	bmp_file image_new;
	algorithm algo;

	if(argc != 3) {
		printf("ERROR: There must be exactly 2 arguments\n");
		return 1;
	}

	image.path     = argv[1];
	image_new.path = argv[2];

	algo.bmp=&image;

	if(bmp_open(&image, "r") == 1)
		return 1;
	if(bmp_read_header(&image) == 1) {
		bmp_close(&image);
		return 1;
	}

	buffer = malloc(image.size_file*sizeof(char));
	bmp_dump_header(&image, buffer);

	bmp_read_image(&image);
	bmp_close(&image);

	apply_algo(&algo);

	if(bmp_open(&image_new, "w+") == 1)
		return 1;
	
	bmp_write_image(&image_new, buffer, image.offset);
	bmp_write_image(&image_new, algo.data, (image.size_file-image.offset));

	bmp_close(&image_new);

	bmp_free(&image);
	algo_free(&algo);
	free(buffer);

	return 0;
}

