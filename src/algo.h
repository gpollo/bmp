#include "global.h"
#include "bmp.h"

typedef struct algorithm {
	unsigned char *data;
	int byte_format;

	bmp_file *bmp;
} algorithm;

int apply_algo(algorithm *algo);
int read_pixel(algorithm *algo, int x, int y, unsigned char *pixel);
int write_pixel(algorithm *algo, int x, int y, unsigned char *pixel);
int algo_free(algorithm *algo);
