all: main.cpp
	g++ -Wall -o main main.cpp

clean:
	$(RM) main
