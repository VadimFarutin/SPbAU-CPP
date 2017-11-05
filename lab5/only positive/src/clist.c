#include "../include/clist.h"

void init_list(intrusive_list *list) {
	list->head.next = &list->head;
	list->head.prev = &list->head;
}
void add_node(intrusive_list *list, intrusive_node *node) {
	node->prev = list->head.prev;
	node->next = &list->head;
	list->head.prev->next = node;
	list->head.prev = node;
}
void remove_node(intrusive_list *list, intrusive_node *node) {
	node->next->prev = node->prev;
	node->prev->next = node->next;
}
int get_length(intrusive_list *list) {
	int length = 0;
	intrusive_node *node;
	for (node = &list->head; node->next != &list->head; node = node->next)
		length++;
	return length;
}