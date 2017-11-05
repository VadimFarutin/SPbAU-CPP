all: lab4
bin:
	mkdir -p bin
lab4: bin bin/ms_cli.o bin/mergesort.o 
	gcc bin/ms_cli.o bin/mergesort.o -o lab4
bin/ms_cli.o: src/ms_cli.c include/mergesort.h 
	gcc -c src/ms_cli.c -o bin/ms_cli.o
bin/mergesort.o: src/mergesort.c include/mergesort.h
	gcc -c src/mergesort.c -o bin/mergesort.o
clean:
	rm -rf ./bin ./lab4