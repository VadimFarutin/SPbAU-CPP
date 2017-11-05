#include "../include/clist.h"
#include "../include/position.h"
#include <string.h>

void load_text(intrusive_list *list, char *filename) {
	FILE *f = fopen(filename, "rt");
	init_list(list);
	int x, y;
	while (!feof(f)) {
		fscanf(f, "%i %i", &x, &y);
		add_position(list, x, y);
	}
	fclose(f);
}
void load_bin(intrusive_list *list, char *filename) {
	FILE *f = fopen(filename, "rb");
	init_list(list);
	int x, y;
	unsigned char buf[6];
	while (fread(buf, 1, 6, f) == 6) {
		x = buf[2] * (1 << 16) + buf[1] * (1 << 8) + buf[0];
		if (buf[2] & (1 << 7))
			x -= (1 << 24);
		y = buf[5] * (1 << 16) + buf[4] * (1 << 8) + buf[3];
		if (buf[5] & (1 << 7))
			y -= (1 << 24);
		add_position(list, x, y);
	}
	fclose(f);
}
void save_text(intrusive_list *list, char *filename) {
	FILE *f = fopen(filename, "wt");
	intrusive_node *intr_node;
	for (intr_node = list->head.next; intr_node != &list->head; intr_node = intr_node->next) {
		position_node *pos_node = container_of(intr_node, position_node, node);
		if (intr_node != list->head.next)
			fprintf(f, "\n");
		fprintf(f, "%i %i", pos_node->x, pos_node->y);
	}
	fclose(f);
}
void save_bin(intrusive_list *list, char *filename) {
	FILE *f = fopen(filename, "wb");
	unsigned char buf[6];
	intrusive_node *intr_node;
	int x, y;
	for (intr_node = list->head.next; intr_node != &list->head; intr_node = intr_node->next) {
		position_node *pos_node = container_of(intr_node, position_node, node);
		x = pos_node->x;
		if (pos_node->x < 0)
			x = (1 << 23) + x;
		y = pos_node->y;
		if (pos_node->y < 0)
			y = (1 << 23) + y;
		buf[0] = x % (1 << 8);
		buf[1] = (x / (1 << 8)) % (1 << 16);
		buf[2] = x / (1 << 16);
		if (pos_node->x < 0)
			buf[2] = buf[2] | (1 << 7);
		buf[3] = y % (1 << 8);
		buf[4] = (y / (1 << 8)) % (1 << 16);
		buf[5] = y / (1 << 16);
		if (pos_node->y < 0)
			buf[5] = buf[5] | (1 << 7);
		fwrite(buf, 1, 6, f);
	}
	fclose(f);
}

void print(void *intr_node, void *format) {
	position_node *pos_node = container_of((intrusive_node *)intr_node, position_node, node);
	printf((char *)format, pos_node->x, pos_node->y);
}
void count(void *intr_node, void *cnt) {
	(*(int *)cnt)++;
}
void apply(intrusive_list *list, void (*op)(void *, void *), void *arg) {
	intrusive_node *intr_node;
	for (intr_node = list->head.next; intr_node != &list->head; intr_node = intr_node->next)
		op(intr_node, arg);
}

void main(int argc, char *argv[]) {
	intrusive_list list;
	char *loadmode = argv[1];
	char *input = argv[2];
	char *action = argv[3];
	char *output, *format;
	int cnt;

	if (strcmp(loadmode, "loadtext") == 0)
		load_text(&list, input);
	else
		load_bin(&list, input);
	if (strcmp(action, "savetext") == 0) {
		output = argv[4];
		save_text(&list, output);
	}
	else if (strcmp(action, "savebin") == 0) {
		output = argv[4];
		save_bin(&list, output);
	}
	else if (strcmp(action, "print") == 0) {
		format = argv[4];
		apply(&list, print, format);
	}
	else {
		cnt = 0;
		apply(&list, count, &cnt);
		printf("%i\n", cnt);
	}
	remove_all(&list);
}