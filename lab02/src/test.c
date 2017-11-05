#include "../include/test_str.h"

void main() {
	char str1[] = "Hello";
	char str2[] = "World";
	test_strcpy(str1, str2);
	test_strcat(str1, str2);
	test_strcmp(str1, str2);
	test_strlen(str1);
}