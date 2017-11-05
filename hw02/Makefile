CXX = g++
CXXFLAGS = -O2 -Wall -Werror -std=c++03 -Iinclude
LDFLAGS = 

all: main

bin:
	mkdir -p bin

main: bin bin/main.o bin/Board.o bin/BoardView.o bin/NcursesBoardView.o
	$(CXX) bin/main.o bin/Board.o bin/BoardView.o bin/NcursesBoardView.o -lncurses -o main $(LDFLAGS)

bin/main.o: src/main.cpp include/Board.h include/BoardView.h include/NcursesBoardView.h
	$(CXX) $(CXXFLAGS) -c  src/main.cpp -o bin/main.o

bin/Board.o: src/Board.cpp include/Board.h
	$(CXX) $(CXXFLAGS) -c  src/Board.cpp -o bin/Board.o

bin/BoardView.o: src/BoardView.cpp include/Board.h include/BoardView.h
	$(CXX) $(CXXFLAGS) -c  src/BoardView.cpp -o bin/BoardView.o

bin/NcursesBoardView.o: src/NcursesBoardView.cpp include/Board.h include/NcursesBoardView.h
	$(CXX) $(CXXFLAGS) -c  src/NcursesBoardView.cpp -o bin/NcursesBoardView.o

test: bin bin/tests.o bin/Test.o bin/BoardTest.o bin/Board.o
	$(CXX) bin/tests.o bin/Test.o bin/BoardTest.o bin/Board.o -o test $(LDFLAGS)

bin/tests.o: test_src/tests.cpp include/BoardTest.h
	$(CXX) $(CXXFLAGS) -c  test_src/tests.cpp -o bin/tests.o

bin/Test.o: test_src/Test.cpp include/Test.h
	$(CXX) $(CXXFLAGS) -c  test_src/Test.cpp -o bin/Test.o

bin/BoardTest.o: test_src/BoardTest.cpp include/Test.h include/BoardTest.h
	$(CXX) $(CXXFLAGS) -c  test_src/BoardTest.cpp -o bin/BoardTest.o

clean:
	rm -rf ./bin ./main ./test

.PHONY: clean all test

