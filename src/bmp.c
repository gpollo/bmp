#include "bmp.h"
#include "io.h"

#define BMP_SIG_B0 66
#define BMP_SIG_B1 77

int bmp_open(bmp_file *bmp, char *perm) {
	bmp->file = fopen(bmp->path, perm);
	
	if(bmp->file == NULL) {
		printf("ERROR: Could not open file '%s'\n", bmp->path);
		return 1;
	}

	return 0;
}

int bmp_close(bmp_file *bmp) {
	fclose(bmp->file);

	return 0;
}

int bmp_read_header(bmp_file *bmp) {
	int temp;

	/* Bitmap file header contains 14 bytes */
	readin_buffer(bmp->file, bmp->buffer, 14);

	/* First 2 bytes: Signature */
	if(bmp->buffer[0] != BMP_SIG_B0 || bmp->buffer[1] != BMP_SIG_B1) {
		printf("ERROR: File '%s' is not a valid BMP file\n", bmp->path);
		return 1;
	}

	/* Next 4 bytes: File Size */
	bmp->size_file = (bmp->buffer[5] << 24) + (bmp->buffer[4] << 16) + (bmp->buffer[3] << 8) + bmp->buffer[2];

	/* Next 4 bytes: Useless */
	/* Next 4 bytes: Offset where the pixel start */
	bmp->offset = (bmp->buffer[13] << 24) + (bmp->buffer[12] << 16) + (bmp->buffer[11] << 8) + bmp->buffer[10];

	/* DIB header contains OFFSET-14 bytes */
	temp = bmp->offset-14;
	readin_buffer(bmp->file, bmp->buffer, temp);

	/* First 4 bytes: DIB header size */
	bmp->size_DIB = (bmp->buffer[3] << 24) + (bmp->buffer[2] << 16) + (bmp->buffer[1] << 8) + bmp->buffer[0];
	if(bmp->size_DIB != temp) {
		printf("ERROR: Mismatch DIB header size\n");
		return 1;
	}

	/* Next 4 bytes: Width */
	bmp->width = (bmp->buffer[7] << 24) + (bmp->buffer[6] << 16) + (bmp->buffer[5] << 8) + bmp->buffer[4];

	/* Next 4 bytes: Height */
	bmp->height = (bmp->buffer[11] << 24) + (bmp->buffer[10] << 16) + (bmp->buffer[9] << 8) + bmp->buffer[8];

	/* Next 2 bytes: Plane (Useless) */
	/* Next 2 bytes: Bits per pixel */
	bmp->bPP = (bmp->buffer[15] << 8) + bmp->buffer[14];
	bmp->BPP = bmp->bPP/8;

	/* Next 4 bytes: Compression */
	temp = (bmp->buffer[19] << 24) + (bmp->buffer[18] << 16) + (bmp->buffer[17] << 8) + bmp->buffer[16];
	if(temp != 0) {
		printf("ERROR: Only uncompressed bitmap are supported\n");
		return 1;
	}

	/* Next 4 bytes: Image size */
	temp = bmp->BPP*(bmp->width*bmp->height);
	bmp->size_image = (bmp->buffer[23] << 24) + (bmp->buffer[22] << 16) + (bmp->buffer[21] << 8) + bmp->buffer[20];
	if(bmp->size_image != temp) {
		printf("ERROR: Mismatch image size\n");
		return 1;
	}

#if DEBUG
	printf("\n");
	printf(" File size: %d\n", bmp->size_file);
	printf("    Offset: %d\n", bmp->offset);
	printf("  DIB size: %d\n", bmp->size_DIB);
	printf("     Width: %d\n", bmp->width);
	printf("    Height: %d\n", bmp->height);
	printf("       bPP: %d\n", bmp->bPP);
	printf("       BPP: %d\n", bmp->BPP);
	printf("Image size: %d\n", bmp->size_image);
	printf("\n");
#endif

	return 0;
}

int bmp_read_image(bmp_file *bmp) {
	bmp->data = malloc(bmp->size_image*sizeof(char));

	readin_buffer(bmp->file, bmp->data, bmp->size_image);

	return 0;
}

int bmp_dump_header(bmp_file *bmp, unsigned char *buffer) {
	rewind(bmp->file);
	readin_buffer(bmp->file, buffer, bmp->offset);

	return 0;
}

int bmp_write_image(bmp_file *bmp, unsigned char *buffer, int size) {
	writeout_buffer(bmp->file, buffer, size);

	return 0;
}

int bmp_free(bmp_file *bmp) {
	free(bmp->data);

	return 0;
}
