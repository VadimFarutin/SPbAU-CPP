#include <stdio.h>
#include "../include/mergesort.h"

void main(int argc, char *argv[]) {
	char *type = argv[1];
	char **elems = (char **)malloc(sizeof(char *) * (argc - 2));
	int i;
	for (i = 2; i < argc; i++)
		*(elems + i - 2) = argv[i];
	if (strcmp(type, "int") == 0) {
		int *elems_i = malloc(sizeof(int) * (argc - 1));
		for (i = 0; i < argc - 2; i++) {
			int j, value = 0, minus = 1;
			int lenght = strlen(*(elems + i));
			for (j = 0; j < lenght; j++) {
				if (*(*(elems + i) + j) == '-') {
					minus = -1;
					continue;
				}
				value *= 10;
				value += *(*(elems + i) + j) - '0';
			}
			*(elems_i + i) = minus * value;
		}
		mergesort(elems_i, argc - 2, sizeof(int), cmp_i);
		for (i = 0; i < argc - 2; i++)
			printf("%i ", *(elems_i + i));
		free(elems_i);
	}
	else if (strcmp(type, "char") == 0) {
		char *elems_c = malloc(sizeof(char) * (argc - 1));
		for (i = 0; i < argc - 2; i++)
			*(elems_c + i) = *(elems + i)[0];
		mergesort(elems_c, argc - 2, sizeof(char), cmp_c);
		for (i = 0; i < argc - 2; i++)
			printf("%c ", *(elems_c + i));
		free(elems_c);
	}
	else {
		int maxlen = 0;
		for (i = 0; i < argc - 2; i++)
			maxlen = (maxlen > strlen(*(elems + i)) ? maxlen : strlen(*(elems + i)));
		char *elems_s = malloc(++maxlen * sizeof(char) * (argc - 2));
		for (i = 0; i < argc - 2; i++) {
			int j;
			for (j = 0; j < strlen(*(elems + i)); j++) {
				*(elems_s + i * maxlen + j) = *(*(elems + i) + j);
			}
			for (j = strlen(*(elems + i)); j < maxlen; j++) {
				*(elems_s + i * maxlen + j) = 0;
			}
		}
		mergesort(elems_s, argc - 2, maxlen, cmp_s);
		int j;
		for (j = 0; j < argc - 2; j++) {
			for (i = 0; i < maxlen; i++)
				printf("%c", *(elems_s + j * maxlen + i));
			printf(" ");
		}
		free(elems_s);
	}
	printf("\n");
	free(elems);
}