#ifndef _SORT_H_
#define _SORT_H_

#include <stddef.h>
#include <string.h>
#include <stdlib.h> 

typedef int (*cmp_t)(const void *, const void *);

void mergesort(void *array, size_t size, size_t elem_size, cmp_t cmp);
int cmp_i(const void *p1, const void *p2);
int cmp_c(const void *p1, const void *p2);
int cmp_s(const void *p1, const void *p2);

#endif