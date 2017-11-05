#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "expat.h"
#include "../include/phonebook.h"
#include "../include/names.h"
#define BUFFER_SIZE 100000

typedef struct context_s {
	phonebook_t *book;
	int phone_index;
} context_t;

void start_element(void *data, const char *element, const char **attribute) {
	human_t *human;
	int i;
	char *pch;
	if (!strcmp(element, "human")) {
		human = malloc(sizeof(human_t));

		char delim[] = " ";
		pch = strtok(attribute[1], delim);
		strcpy(human->name, pch);
		pch = strtok(NULL, delim);
		strcpy(human->middle_name, pch);
		pch = strtok(NULL, delim);
		strcpy(human->family_name, pch);

		for (i = 0; i < 10; i++)
			human->phones[i][0] = -1;
		push_back_human(((context_t *)data)->book, human);
		((context_t *)data)->phone_index = 0;
		free(human);
	}
}

void end_element(void *data, const char *element) {
	if (!strcmp(element, "phone"))
		((context_t *)data)->phone_index++;
}

void handle_data(void *data, const char *content, int length) {
	char *tmp = malloc(length + 1);
	context_t *context = (context_t *)data;
	int index = context->phone_index;
	strncpy(tmp, content, length);
	tmp[length] = '\0';
	if ('0' <= tmp[0] && tmp[0] <= '9') {
		if (context->book->humans[context->book->size - 1].phones[index][0] == -1)
			strcpy(context->book->humans[context->book->size - 1].phones[index], tmp);
		else
			strcat(context->book->humans[context->book->size - 1].phones[index], tmp);
	}
	free(tmp);
}

int cmp(const void *a, const void *b) {
	return strcmp(((human_t *)a)->family_name, ((human_t *)b)->family_name);
}
int load_phonebook_xml(const char *filename, phonebook_t *book) {
	char buffer[BUFFER_SIZE];
	FILE *fp;
	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Failed to open file\n");
		return 1;
	}
	context_t *context = malloc(sizeof(context_t));
	context->book = book;
	context->phone_index = 0;

	XML_Parser parser = XML_ParserCreate(NULL);
	XML_SetElementHandler(parser, start_element, end_element);
	XML_SetCharacterDataHandler(parser, handle_data);
	XML_SetUserData(parser, context);

	memset(buffer, 0, BUFFER_SIZE);

	size_t len = 0;
	int done = 0;
	do {
		len = fread(buffer, sizeof(char), BUFFER_SIZE, fp);
		done = len < BUFFER_SIZE;

		if (XML_Parse(parser, buffer, len, done) == XML_STATUS_ERROR) {
			printf("Error: %s\n", XML_ErrorString(XML_GetErrorCode(parser)));
			return 2;
		}
	} while (!done);

	qsort(book->humans, book->size, sizeof(human_t), cmp);
	free(context);
	XML_ParserFree(parser);
	fclose(fp);
	return 0;
}

int save_phonebook_xml(const char *filename, phonebook_t *book) {
	int i, j;
	FILE *fp;
	fp = fopen(filename, "w");
	if (fp == NULL) {
		printf("Failed to open file\n");
		return 1;
	}

	fprintf(fp, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
	fprintf(fp, "<phonebook>\n");
	for (i = 0; i < book->size; i++) {
		fprintf(fp, "    <human name=\"%s %s %s\">\n", book->humans[i].name, book->humans[i].middle_name, book->humans[i].family_name);
		j = 0;
		while (j < 10 && book->humans[i].phones[j][0] != -1) {
			fprintf(fp, "        <phone>%s</phone>\n", book->humans[i].phones[j]);
			j++;
		}
		fprintf(fp, "    </human>\n");
	}
	fprintf(fp, "</phonebook>");
	fclose(fp);
	return 0;
}

void print_phonebook(phonebook_t *book) {
	printf("%i\n", (unsigned int)book->size);
	int i, j;
	for (i = 0; i < book->size; i++) {
		printf("name: %s\n", book->humans[i].name);
		printf("middle name: %s\n", book->humans[i].middle_name);
		printf("family name: %s\n", book->humans[i].family_name);
		j = 0;
		while (j < 10 && book->humans[i].phones[j][0] != -1) {
			printf("phone: %s\n", book->humans[i].phones[j]);
			j++;
		}
		printf("\n");
	}
}
void gen_phonebook(phonebook_t *book, size_t size) {
	clear_phonebook(book);
	int i, j, k, phones_cnt, phone_len;
	char phone[21];
	srand(time(NULL));
	human_t *human = malloc(sizeof(human_t));
	for (i = 0; i < size; i++) {
		for (j = 0; j < 10; j++)
			human->phones[j][0] = -1;
		strcpy(human->name, kNames[rand() % NAMES_CNT]);
		strcpy(human->middle_name, kMiddleNames[rand() % MIDDLE_NAMES_CNT]);
		strcpy(human->family_name, kFamilyNames[rand() % FAMILY_NAMES_CNT]);
		phones_cnt = rand() % 10;
		for (j = 0; j < phones_cnt; j++) {
			phone_len = rand() % 19 + 1;
			for (k = 0; k < phone_len; k++)
				phone[k] = rand() % 10 + '0';
			phone[k] = '\0';
			strcpy(human->phones[j], phone);
		}
		push_back_human(book, human);
	}
	free(human);
}
void clear_phonebook(phonebook_t *book) {
	book->size = 0;
	book->capacity = 0;
	free(book->humans);
}

human_t get_human(phonebook_t *book, char* family_name) {
	int i;
	for (i = 0; i < book->size; i++)
		if (!strcmp(book->humans[i].family_name, family_name))
			return book->humans[i];
}

void push_back_human(phonebook_t *book, human_t *human) {
	if (book->size == book->capacity) {
		if (book->capacity == 0) {
			book->capacity = 2;
			book->humans = malloc(sizeof(human_t) * book->capacity);
		}
		else {
			book->capacity *= 2;
			book->humans = realloc(book->humans, sizeof(human_t) * book->capacity);
		}
	}
	book->humans[book->size++] = *human;
}