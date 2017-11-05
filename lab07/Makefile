all: lab7
bin:
	mkdir -p bin
lab7: bin bin/main.o bin/my_vector.o
	g++ -std=c++0x bin/main.o bin/my_vector.o -o lab7
bin/main.o: src/main.cpp include/my_vector.h
	g++ -c -std=c++0x src/main.cpp -o bin/main.o
bin/my_vector.o: src/my_vector.cpp include/my_vector.h
	g++ -c -std=c++0x src/my_vector.cpp -o bin/my_vector.o
clean:
	rm -rf ./bin ./lab7
