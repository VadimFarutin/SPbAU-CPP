#include <stdlib.h>
#include <stddef.h>
#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))

typedef struct intrusive_node
{
	struct intrusive_node *next;
	struct intrusive_node *prev;
} intrusive_node;

typedef struct intrusive_list
{
	intrusive_node head;
} intrusive_list;

typedef struct position_node
{
	int x, y;
	intrusive_node node;
} position_node;

void init_list(intrusive_list *list);
void add_node(intrusive_list *list, intrusive_node *node);
void remove_node(intrusive_list *list, intrusive_node *node);
int get_length(intrusive_list *list);