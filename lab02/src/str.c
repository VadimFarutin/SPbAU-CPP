#include "../include/str.h"

char *strcpy_my(char *destination, const char *source) {
	int i;
	for (i = 0; *(source + i) != 0; i++)
		*(destination + i) = *(source + i);
	*(destination + i) = 0;
	return destination;
}
char *strcat_my(char *destination, const char *source) {
	int i;
	for (i = 0; *(destination + i) != 0; i++)
		;
	int j;
	for (j = 0; *(source + j) != 0; j++)
		*(destination + i + j) = *(source + j);
	*(destination + i + j) = 0;
	return destination;
}
int strcmp_my(const char *str1, const char *str2) {
	int i;
	for (i = 0; *(str1 + i) != 0 && *(str2 + i) != 0; i++) {
		if (*(str1 + i) < *(str2 + i))
			return -1;
		if (*(str1 + i) > *(str2 + i))
			return 1;
	}
	if (*(str1 + i) != 0)
		return 1;
	if (*(str2 + i) != 0)
		return -1;
	return 0;
}
size_t strlen_my(const char *str) {
	size_t len;
	for (len = 0; *(str + len) != 0; len++)
		;
	return len;
}