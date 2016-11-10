all: main.cpp
	g++ -std=c++0x -Wall -o main main.cpp expression.cpp expression_factory.cpp

clean:
	$(RM) main
