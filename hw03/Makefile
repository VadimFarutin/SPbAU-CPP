CXX = g++
CXXFLAGS = -O2 -pedantic -Wall -Werror -std=c++11 -Isrc -Itest
LDFLAGS = 

all: huffman

bin:
	mkdir -p bin

huffman: bin bin/main.o bin/huffman.o bin/bit_stream.o
	$(CXX) bin/main.o bin/huffman.o bin/bit_stream.o -o bin/huffman $(LDFLAGS)

bin/main.o: src/main.cpp src/huffman.h
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o bin/main.o

bin/bit_stream.o: src/bit_stream.cpp src/bit_stream.h
	$(CXX) $(CXXFLAGS) -c src/bit_stream.cpp -o bin/bit_stream.o

bin/huffman.o: src/huffman.cpp src/huffman.h src/bit_stream.h
	$(CXX) $(CXXFLAGS) -c src/huffman.cpp -o bin/huffman.o

test: bin bin/test.o bin/autotest.o bin/huffman_test.o bin/huffman.o bin/bit_stream.o
	$(CXX) bin/test.o bin/autotest.o bin/huffman_test.o bin/huffman.o bin/bit_stream.o -o bin/test $(LDFLAGS)

bin/test.o: test/test.cpp test/huffman_test.h
	$(CXX) $(CXXFLAGS) -c test/test.cpp -o bin/test.o

bin/autotest.o: test/autotest.cpp test/autotest.h
	$(CXX) $(CXXFLAGS) -c test/autotest.cpp -o bin/autotest.o

bin/huffman_test.o: src/huffman.h test/huffman_test.cpp test/huffman_test.h
	$(CXX) $(CXXFLAGS) -c test/huffman_test.cpp -o bin/huffman_test.o

clean:
	rm -rf ./bin

.PHONY: clean all