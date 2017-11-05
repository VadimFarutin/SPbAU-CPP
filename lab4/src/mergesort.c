#include "../include/mergesort.h"

int cmp_i(const void *p1, const void *p2) {
	return *(int *)p1 - *(int *)p2;
}
int cmp_c(const void *p1, const void *p2) {
	return *(char *)p1 - *(char *)p2;
}
int cmp_s(const void *p1, const void *p2) {
	return strcmp((char *)p1, (char *)p2);
}
void copy(void *dest, const void *src, size_t size) {
	char *dest_c = (char *)dest;
	char *src_c = (char *)src;
	size_t i;
	for (i = 0; i < size; i++)
		*(dest_c + i) = *(src_c + i);
}
void mergesort(void *array, size_t size, size_t elem_size, cmp_t cmp) {
	if (size == 1)
		return;
	size_t half = size / 2;
	char *array_c = (char *)array;
	char *half_c = array_c + half * elem_size;
	char *end_c = array_c + size * elem_size;
	
	mergesort(array_c, half, elem_size, cmp);
	mergesort(half_c, size - half, elem_size, cmp);
	
	char *copy_c = (char *)malloc(size * elem_size);
	char *i, *ptr1 = array_c, *ptr2 = half_c;
	for (i = copy_c; i < copy_c + size * elem_size; i += elem_size) {
		if (ptr1 == half_c || (ptr2 != end_c && cmp(ptr1, ptr2) > 0)) {
			copy(i, ptr2, elem_size);
			ptr2 += elem_size;
		}
		else {
			copy(i, ptr1, elem_size);
			ptr1 += elem_size;
		}
	}
	copy(array_c, copy_c, size * elem_size);
	free(copy_c);
}