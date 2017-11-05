#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bmp.h"

int main(int argc, char **argv) {
	if (argc != 8) {
		printf("Wrong number of arguments\n");
		return 1;
	}

	if (strcmp(argv[1], "crop-rotate")) {
		printf("Unknown command\n");
		return 1;
	}

    bmp_file_t bmp_file;
    unsigned int x, y;
	int w, h;

    if (sscanf(argv[4], "%u", &x) != 1) {
		printf("Failed to read fourth argument\n");
		return 1;
	}

	if (sscanf(argv[5], "%u", &y) != 1) {
		printf("Failed to read fifth argument\n");
		return 1;
	}

	if (sscanf(argv[6], "%i", &w) != 1) {
		printf("Failed to read sixth argument\n");
		return 1;
	}

	if (sscanf(argv[7], "%i", &h) != 1) {
		printf("Failed to read seventh argument\n");
		return 1;
	}

    if (load_bmp(argv[2], &bmp_file) == 1)
		return 1;
	if (crop(&bmp_file, x, y, w, h) == 1)
		return 1;
	if (rotate(&bmp_file) == 1)
		return 1;
    if (save_bmp(argv[3], &bmp_file) == 1)
		return 1;

	free(bmp_file.pixels);

	return 0;
}
