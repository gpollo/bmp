#include "algo.h"

int apply_algo(algorithm *algo) {
	unsigned char *pixel;
	char direction[2];
	int iteration[3];
	int i;
	int x[3];
	int y[3];

	algo->byte_format = algo->bmp->BPP;

	algo->data = malloc(algo->bmp->size_image*sizeof(char));
	pixel = malloc(algo->byte_format*sizeof(char));

	iteration[0] = algo->bmp->width;
	iteration[1] = iteration[0]*iteration[0];
	iteration[2] = iteration[0]/2;

	x[0]=0;
	x[1]=0;
	x[2]=0;
	y[0]=0;
	y[1]=0;
	y[2]=0;
	direction[0] = 0;
	direction[1] = 0;

	for(i=0; i<iteration[1]; i++) {
		read_pixel(algo, x[0], y[0], pixel);

		if(direction[0] == 0) {
			direction[0] = 1;
			x[2] = x[1];
		} else {
			direction[0] = 0;
			x[2] = x[1]+iteration[2];
			x[1] = x[1]+1;
		}

		if(direction[1] == 0) {
			y[2] = y[1];
		} else {
			y[2] = y[1]+iteration[2];
		}

		if(x[1] == iteration[2]) {
			x[1] = 0;
			if(direction[1] == 0)
				direction[1] = 1;
			else {
				direction[1] = 0;
				y[1] = y[1]+1;
			}
		}

		write_pixel(algo, x[2], y[2], pixel);

		x[0] = x[0]+1;
		if(x[0] == iteration[0]) {
			x[0] = 0;
			y[0] = y[0]+1;
		}	
	}
	free(pixel);
	return 0;
}

int read_pixel(algorithm *algo, int x, int y, unsigned char *pixel) {
	int p;

	p = 3*(x+(algo->bmp->width*y));

	pixel[0] = algo->bmp->data[p+0];
	pixel[1] = algo->bmp->data[p+1];
	pixel[2] = algo->bmp->data[p+2];

	return 0;
}

int write_pixel(algorithm *algo, int x, int y, unsigned char *pixel) {
	int p;

	p = 3*(x+(algo->bmp->width*y));

	algo->data[p+0] = pixel[0];
	algo->data[p+1] = pixel[1];
	algo->data[p+2] = pixel[2];

	return 0;
}

int algo_free(algorithm *algo) {
	free(algo->data);

	return 0;
}
