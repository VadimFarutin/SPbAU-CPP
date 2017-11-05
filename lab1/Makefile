lab1.exe: bin/main.o bin/io.o bin/util.o bin/algorithm.o
	gcc bin/main.o bin/io.o bin/util.o bin/algorithm.o -o lab1
bin/main.o: src/main.c include/io.h include/util.h include/algorithm.h
	gcc -c src/main.c -o bin/main.o
bin/io.o: src/io.c include/io.h
	gcc -c src/io.c -o bin/io.o
bin/util.o: src/util.c include/util.h include/io.h 
	gcc -c src/util.c -o bin/util.o
bin/algorithm.o: src/algorithm.c include/algorithm.h include/io.h include/util.h
	gcc -c src/algorithm.c -o bin/algorithm.o	
all: lab1.exe
clean: 
	rm ./bin/*.o ./lab1.exe
	