all: main
bin:
	mkdir -p bin
main: bin bin/main.o bin/bmp.o
	gcc bin/main.o bin/bmp.o -o main
bin/main.o: src/main.c include/bmp.h
	gcc -c -std=c99 -Iinclude -Wall -Werror src/main.c -o bin/main.o
bin/bmp.o: src/bmp.c include/bmp.h
	gcc -c -std=c99 -Iinclude -Wall -Werror src/bmp.c -o bin/bmp.o
clean:
	rm -rf ./bin ./main

