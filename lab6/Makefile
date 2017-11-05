all: main
bin:
	mkdir -p bin
main: bin bin/main.o bin/phonebook.o
	gcc bin/main.o bin/phonebook.o -lexpat -o main
bin/main.o: src/main.c include/phonebook.h
	gcc -c -w src/main.c -o bin/main.o
bin/phonebook.o: src/phonebook.c include/phonebook.h
	gcc -c -w src/phonebook.c -o bin/phonebook.o
clean:
	rm -rf ./bin ./main

