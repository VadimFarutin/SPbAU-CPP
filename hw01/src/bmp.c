#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"

#define FILE_HEADER_SIZE 14
#define INFO_HEADER_SIZE 40

int read_file_header(FILE *f, bmp_file_t *bmp_file) {
	fread(&(bmp_file->file_h.type), sizeof(unsigned short), 1, f);
	fread(&(bmp_file->file_h.size), sizeof(unsigned int), 1, f);
	fread(&(bmp_file->file_h.reserved1), sizeof(unsigned short), 1, f);
	fread(&(bmp_file->file_h.reserved2), sizeof(unsigned short), 1, f);
	fread(&(bmp_file->file_h.off_bits), sizeof(unsigned int), 1, f);

	if (ferror(f))
		return 1;
	return 0;
}

void print_file_header(bmp_file_t *bmp_file) {
	printf("\n%hu\n", bmp_file->file_h.type);
	printf("%u\n", bmp_file->file_h.size);
	printf("%hu\n", bmp_file->file_h.reserved1);
	printf("%hu\n", bmp_file->file_h.reserved2);
	printf("%u\n", bmp_file->file_h.off_bits);
}

int read_info_header(FILE *f, bmp_file_t *bmp_file) {
	fread(&(bmp_file->info_h.size), sizeof(unsigned int), 1, f);
	fread(&(bmp_file->info_h.w), sizeof(int), 1, f);
	fread(&(bmp_file->info_h.h), sizeof(int), 1, f);
	fread(&(bmp_file->info_h.planes), sizeof(unsigned short), 1, f);
	fread(&(bmp_file->info_h.bit_count), sizeof(unsigned short), 1, f);
	fread(&(bmp_file->info_h.compression), sizeof(unsigned int), 1, f);
	fread(&(bmp_file->info_h.size_image), sizeof(unsigned int), 1, f);
	fread(&(bmp_file->info_h.x_pels_per_meter), sizeof(int), 1, f);
	fread(&(bmp_file->info_h.y_pels_per_meter), sizeof(int), 1, f);
	fread(&(bmp_file->info_h.clr_used), sizeof(unsigned int), 1, f);
	fread(&(bmp_file->info_h.clr_important), sizeof(unsigned int), 1, f);

	if (ferror(f))
		return 1;
	return 0;
}

void print_info_header(bmp_file_t *bmp_file) {
	printf("\n%u\n", bmp_file->info_h.size);
	printf("%i\n", bmp_file->info_h.w);
	printf("%i\n", bmp_file->info_h.h);
	printf("%hu\n", bmp_file->info_h.planes);
	printf("%hu\n", bmp_file->info_h.bit_count);
	printf("%u\n", bmp_file->info_h.compression);
	printf("%u\n", bmp_file->info_h.size_image);
	printf("%i\n", bmp_file->info_h.x_pels_per_meter);
	printf("%i\n", bmp_file->info_h.y_pels_per_meter);
	printf("%u\n", bmp_file->info_h.clr_used);
	printf("%u\n", bmp_file->info_h.clr_important);
}

/*
*  Calculates increased value of width in bytes
*  so that it is divided by four
*/
int raw_bytes(int width) {
	return 3 * width + (4 - (3 * width) % 4) % 4;
}

void swap(int *a, int *b) {
	int t = *a;
	*a = *b;
	*b = t;
}

int load_bmp(const char *filename, bmp_file_t *bmp_file) {
	FILE *f = fopen(filename, "rb");
	
	if (f == NULL) {
		printf("Failed to open file\n");
		return 1;
	}

	if (read_file_header(f, bmp_file) == 1) {
		printf("Failed to read file header\n");
		return 1;
	}

	if (read_info_header(f, bmp_file) == 1) {
		printf("Failed to read info header\n");
		return 1;
	}


	bmp_info_header_t *info_h = &bmp_file->info_h;
	int row_size = raw_bytes(info_h->w);
	bmp_file->pixels = malloc(row_size * info_h->h);
	
	if (bmp_file->pixels == NULL) {
		printf("Failed to allocate memory\n");
		return 1;
	}

	fread(bmp_file->pixels, sizeof(unsigned char), row_size * info_h->h, f);
	
	if (ferror(f)) {
		printf("Failed to read pixels\n");
		return 1;
	}

	if (fclose(f) != 0) {
		printf("Failed to close file\n");
		return 1;
	}

	return 0;
}

int check_arguments(bmp_file_t *bmp_file, unsigned int x, unsigned int y, int crop_w, int crop_h) {
	int width = bmp_file->info_h.w;
	int height = bmp_file->info_h.h;

	if (crop_w <= 0 || crop_h <= 0)  {
		printf("Height and width must be positive\n");
		return 1;
	}

	if (x < 0 || x >= width || y < 0 || y >= height)  {
		printf("Coordinates are out of bounds\n");
		return 1;
	}

	if (x + crop_w > width)  {
		printf("New width is too big\n");
		return 1;
	}

	if (y + crop_h > height)  {
		printf("New height is too big\n");
		return 1;
	}

	return 0;
}

void update_header(bmp_file_t *bmp_file, unsigned char *pixels, int width, int height) {
	bmp_info_header_t *info_h = &bmp_file->info_h;

	bmp_file->pixels = pixels;
	info_h->size_image = raw_bytes(width) * height;
	bmp_file->file_h.size = info_h->size_image + FILE_HEADER_SIZE + INFO_HEADER_SIZE;
	info_h->w = width;
	info_h->h = height;
}

int crop(bmp_file_t *bmp_file, unsigned int x, unsigned int y, int crop_w, int crop_h) {
	if (check_arguments(bmp_file, x, y, crop_w, crop_h) == 1)
		return 1;

	int width = bmp_file->info_h.w;
	int height = bmp_file->info_h.h;
	int row_size = raw_bytes(crop_w);
	int old_row_size = raw_bytes(width);
	unsigned char *old_pixels = bmp_file->pixels;
	unsigned char *pixels = malloc(row_size * crop_h);

	if (pixels == NULL) {
		printf("Failed to allocate memory\n");
		return 1;
	}

	memset(pixels, 0, row_size * crop_h);
	int i, line_number;
	unsigned char *dst, *src;

	for (i = 0; i < crop_h; i++) {
		dst = pixels + row_size * i;
		line_number = height - y - crop_h + i;
		src = old_pixels + old_row_size * line_number + 3 * x;
		memcpy(dst, src, 3 * crop_w);
	}

	update_header(bmp_file, pixels, crop_w, crop_h);
	free(old_pixels);

	return 0;
}

int rotate(bmp_file_t *bmp_file) {
	int width = bmp_file->info_h.w;
	int height = bmp_file->info_h.h;
	int row_size = raw_bytes(height);
	int old_row_size = raw_bytes(width);
	unsigned char *pixels = bmp_file->pixels;
	unsigned char *rotated = malloc(width * row_size);

	if (rotated == NULL) {
		printf("Failed to allocate memory\n");
		return 1;
	}

	memset(rotated, 0, width * row_size);
	int i, j;
	unsigned char *dst, *src;
	
	for (j = 0; j < width; j++) {
		for (i = 0; i < height; i++) {
			dst = rotated + j * row_size + 3 * i;
			src = pixels + i * old_row_size + 3 * (width - j - 1);
			memcpy(dst, src, 3);
		}
	}

	free(pixels);
	update_header(bmp_file, rotated, bmp_file->info_h.h, bmp_file->info_h.w);

	return 0;
}

int write_file_header(FILE *f, bmp_file_t *bmp_file) {
	fwrite(&(bmp_file->file_h.type), sizeof(unsigned short), 1, f);
	fwrite(&(bmp_file->file_h.size), sizeof(unsigned int), 1, f);
	fwrite(&(bmp_file->file_h.reserved1), sizeof(unsigned short), 1, f);
	fwrite(&(bmp_file->file_h.reserved2), sizeof(unsigned short), 1, f);
	fwrite(&(bmp_file->file_h.off_bits), sizeof(unsigned int), 1, f);

	if (ferror(f))
		return 1;
	return 0;
}

int write_info_header(FILE *f, bmp_file_t *bmp_file) {
	fwrite(&(bmp_file->info_h.size), sizeof(unsigned int), 1, f);
	fwrite(&(bmp_file->info_h.w), sizeof(int), 1, f);
	fwrite(&(bmp_file->info_h.h), sizeof(int), 1, f);
	fwrite(&(bmp_file->info_h.planes), sizeof(unsigned short), 1, f);
	fwrite(&(bmp_file->info_h.bit_count), sizeof(unsigned short), 1, f);
	fwrite(&(bmp_file->info_h.compression), sizeof(unsigned int), 1, f);
	fwrite(&(bmp_file->info_h.size_image), sizeof(unsigned int), 1, f);
	fwrite(&(bmp_file->info_h.x_pels_per_meter), sizeof(int), 1, f);
	fwrite(&(bmp_file->info_h.y_pels_per_meter), sizeof(int), 1, f);
	fwrite(&(bmp_file->info_h.clr_used), sizeof(unsigned int), 1, f);
	fwrite(&(bmp_file->info_h.clr_important), sizeof(unsigned int), 1, f);

	if (ferror(f))
		return 1;
	return 0;
}

int save_bmp(const char *filename, bmp_file_t *bmp_file) {
	FILE *f = fopen(filename, "wb");
	
	if (f == NULL) {
		printf("Failed to open file\n");
		return 1;
	}

	if (write_file_header(f, bmp_file) == 1) {
		printf("Failed to write file header\n");
		return 1;
	}
	
	if (write_info_header(f, bmp_file) == 1) {
		printf("Failed to write info header\n");
		return 1;
	}

	int row_size = raw_bytes(bmp_file->info_h.w);
	fwrite(bmp_file->pixels, sizeof(unsigned char), row_size * bmp_file->info_h.h, f);
	
	if (ferror(f)) {
		printf("Failed to write pixels\n");
		return 1;
	}

	if (fclose(f) != 0) {
		printf("Failed to close file\n");
		return 1;
	}
	
	return 0;
}
