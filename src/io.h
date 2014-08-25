#include <stdio.h>

#include "global.h"

int readin_buffer(FILE *file, unsigned char *buffer, int size);
int writeout_buffer(FILE *file, unsigned char *buffer, int size);
int copybuffer_buffer(unsigned char *buffer1, unsigned char *buffer2);
