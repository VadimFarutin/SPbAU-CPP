all: lab2.exe
bin:
	mkdir -p bin
lab2.exe: bin bin/test.o bin/str.o bin/test_str.o
	gcc bin/test.o bin/str.o bin/test_str.o -o lab2
bin/test.o: src/test.c include/test_str.h 
	gcc -c src/test.c -o bin/test.o
bin/str.o: src/str.c include/str.h
	gcc -c src/str.c -o bin/str.o
bin/test_str.o: src/test_str.c include/test_str.h
	gcc -c src/test_str.c -o bin/test_str.o
clean:
	rm -rf ./bin ./lab2.exe