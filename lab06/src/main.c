#include <stdlib.h>
#include "../include/phonebook.h"

int main(int argc, char **argv) {
	phonebook_t *book = malloc(sizeof(phonebook_t));
	book->size = 0;
	book->capacity = 0;
	load_phonebook_xml(argv[1], book);
	print_phonebook(book);
	gen_phonebook(book, 5);
	save_phonebook_xml(argv[2], book);
	clear_phonebook(book);
	free(book);
	return 0;
}
