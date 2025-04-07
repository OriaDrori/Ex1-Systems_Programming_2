CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic -g

GRAPH_SRC = graph/Graph.cpp graph/Queue.cpp graph/Algorithms.cpp graph/PriorityQueue.cpp graph/UnionFind.cpp
GRAPH_HEADERS = graph/Graph.h graph/Queue.h graph/Algorithms.h graph/PriorityQueue.h graph/UnionFind.h

Main: main.o
	g++ $(CXXFLAGS) -o Main main.o $(GRAPH_SRC)

test: tests.o
	g++ $(CXXFLAGS) -o test tests.o $(GRAPH_SRC)

main.o: main.cpp $(GRAPH_HEADERS)
	g++ $(CXXFLAGS) -c -o main.o main.cpp

tests.o: tests.cpp $(GRAPH_HEADERS)
	g++ $(CXXFLAGS) -c -o tests.o tests.cpp

valgrind: Main
	valgrind --leak-check=full --track-origins=yes ./Main

clean:
	rm -f Main test main.o tests.o
