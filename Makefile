all: main.cpp expression.cpp expression_factory.cpp user.cpp menu.cpp
	g++ -g -std=c++0x -Wall -o main main.cpp expression.cpp expression_factory.cpp user.cpp menu.cpp

clean:
	$(RM) main
