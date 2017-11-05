all: lab5
bin:
	mkdir -p bin
lab5: bin bin/main.o bin/clist.o bin/position.o 
	gcc bin/main.o bin/clist.o bin/position.o -o lab5
bin/main.o: src/main.c include/clist.h include/position.h
	gcc -c src/main.c -o bin/main.o
bin/clist.o: src/clist.c include/clist.h
	gcc -c src/clist.c -o bin/clist.o
bin/position.o: src/position.c include/clist.h include/position.h
	gcc -c src/position.c -o bin/position.o
clean:
	rm -rf ./bin ./lab5