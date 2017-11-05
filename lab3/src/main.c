#include <stdio.h>
#include "../include/clist.h"

void remove_position(intrusive_list *list, int x, int y) {
	intrusive_node del_node;
	intrusive_node *intr_node;
	for (intr_node = list->head.next; intr_node != &list->head; intr_node = intr_node->next) {
		position_node *pos_node = container_of(intr_node, position_node, node);
		if (pos_node->x == x && pos_node->y == y) {
			del_node = *intr_node;
			remove_node(list, intr_node);
			intr_node = &del_node;
			free(pos_node);
		}
	}
}
void add_position(intrusive_list *list, int x, int y) {
	position_node *node = (position_node *)malloc(sizeof(position_node));
	node->x = x;
	node->y = y;
	add_node(list, &node->node);
}
void show_all_positions(intrusive_list *list) {
	intrusive_node *intr_node;
	for (intr_node = list->head.next; intr_node != &list->head; intr_node = intr_node->next) {
		position_node *pos_node = container_of(intr_node, position_node, node);
		printf("(%i %i)\n", pos_node->x, pos_node->y);
	}
}
void remove_all(intrusive_list *list) {
	intrusive_node del_node;
	intrusive_node *intr_node;
	for (intr_node = list->head.next; intr_node != &list->head; intr_node = intr_node->next) {
		position_node *pos_node = container_of(intr_node, position_node, node);
		del_node = *intr_node;
		remove_node(list, intr_node);
		intr_node = &del_node;
		free(pos_node);
	}
}

void main() {
	intrusive_list list;
	init_list(&list);
	add_position(&list, 4, 5);
	add_position(&list, 2, 3);
	add_position(&list, 4, 5);
	add_position(&list, 4, 5);
	add_position(&list, 0, 0);
	show_all_positions(&list);
	remove_position(&list, 4, 5);
	show_all_positions(&list);
	remove_all(&list);
}