all: lab3
bin:
	mkdir -p bin
lab3: bin bin/main.o bin/clist.o 
	gcc bin/main.o bin/clist.o -o lab3
bin/main.o: src/main.c include/clist.h 
	gcc -c src/main.c -o bin/main.o
bin/clist.o: src/clist.c include/clist.h
	gcc -c src/clist.c -o bin/clist.o
clean:
	rm -rf ./bin ./lab3