#include "../include/test_str.h"

void test_strcpy(char *str1, const char *str2) {
	if (strcmp(strcpy_my(str1, str2), str2) == 0)
		printf("strcpy works correctly.\n");
	else
		printf("strcpy works incorrectly!\n");
}
void test_strcat(char *str1, const char *str2) {
	char str3[] = "";
	strcpy(str3, str1);
	if (strcmp(strcat_my(str1, str2), strcat(str3, str2)) == 0)
		printf("strcat works correctly.\n");
	else
		printf("strcat works incorrectly!\n");
}
void test_strcmp(const char *str1, const char *str2) {
	int cmp1 = strcmp_my(str1, str2);
	int cmp2 = strcmp(str1, str2);
	if (cmp1 * cmp2 > 0 || cmp1 == cmp2)
		printf("strcmp works correctly.\n");
	else
		printf("strcmp works incorrectly!\n");
}
void test_strlen(const char *str1) {
	if (strlen_my(str1) == strlen(str1))
		printf("strlen works correctly.\n");
	else
		printf("strlen works incorrectly!\n");
}
