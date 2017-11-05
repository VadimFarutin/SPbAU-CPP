#ifndef _BMP_H_
#define _BMP_H_

typedef struct bmp_file_header_s {
	unsigned short type;
	unsigned int size;
	unsigned short reserved1;
	unsigned short reserved2;
	unsigned int off_bits;
} bmp_file_header_t;

typedef struct bmp_info_header_s {
	unsigned int size;
	int w;
	int h;
	unsigned short planes;
	unsigned short bit_count;
	unsigned int compression;
	unsigned int size_image;
	int x_pels_per_meter;
	int y_pels_per_meter;
	unsigned int clr_used;
	unsigned int clr_important;
} bmp_info_header_t;

typedef struct bmp_file_s {
	bmp_file_header_t file_h;
	bmp_info_header_t info_h;
	unsigned char *pixels;
} bmp_file_t;

int load_bmp(const char *filename, bmp_file_t *bmp_file);
int crop(bmp_file_t *bmp_file, unsigned int x, unsigned int y, int w, int h);
int rotate(bmp_file_t *bmp_file);
int save_bmp(const char *filename, bmp_file_t *bmp_file);

#endif
