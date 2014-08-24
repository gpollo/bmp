#include "bmp.h"
#include "io.h"

#define BMP_SIG_B0 66
#define BMP_SIG_B1 77

int bmp_open(bmp_file *bmp) {
	bmp->file = fopen(bmp->path, "r");
	
	if(bmp->file == NULL) {
		printf("ERROR: Could not open file %s\n", bmp->path);
		return 1;
	}

	return 0;
}

int bmp_close(bmp_file *bmp) {
	fclose(bmp->file);

	return 0;
}

int string_to_int(unsigned char *string) {
    int  i, n;

    n = 0;

    for(i = 0; string[i] != '\0'; i++)
        n = (n*10)+(string[i]-'0');

    return n;
}

int bmp_read_header(bmp_file *bmp) {
	int size;

	/* Bitmap file header contains 14 bytes */
	readin_buffer(bmp->file, bmp->buffer, 14);

	/* First 2 bytes: Signature */
	if(bmp->buffer[0] != BMP_SIG_B0 || bmp->buffer[1] != BMP_SIG_B1) {
		printf("ERROR: File %s is not a valid BMP file\n", bmp->path);
		return 1;
	}

	/* Next 4 bytes: File Size */
	bmp->size_file = (bmp->buffer[5] << 24) + (bmp->buffer[4] << 16) + (bmp->buffer[3] << 8) + bmp->buffer[2];

	/* Next 4 bytes: Useless */
	/* Next 4 bytes: Offset where the pixel start */
	bmp->offset = (bmp->buffer[13] << 24) + (bmp->buffer[12] << 16) + (bmp->buffer[11] << 8) + bmp->buffer[10];

	/* DIB header contains OFFSET-14 bytes */
	size = bmp->offset-14;
	readin_buffer(bmp->file, bmp->buffer, size);

	/* First 4 bytes: DIB header size */
	bmp->size_DIB = (bmp->buffer[3] << 24) + (bmp->buffer[2] << 16) + (bmp->buffer[1] << 8) + bmp->buffer[0];
	if(bmp->size_DIB != size) {
		printf("ERROR: Mismatch DIB header for file %s\n", bmp->path);
		return 1;
	}

	printf("size:%d\n", bmp->size_file);
	printf("offset:%d\n", bmp->size_DIB);

	return 0;
}
