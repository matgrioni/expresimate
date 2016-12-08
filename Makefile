all: main.cpp expression.cpp expression_factory.cpp user.cpp
	g++ -g -std=c++0x -Wall -o main main.cpp expression.cpp expression_factory.cpp user.cpp

clean:
	$(RM) main
