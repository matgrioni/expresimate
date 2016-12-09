OBJS = expression.o expression_factory.o user.o menu.o start.o new_user.o util.o

main: main.cpp $(OBJS)
	g++ -std=c++0x -Wall -o main main.cpp $(OBJS)

expression.o: expression.hpp expression.cpp
	g++ -std=c++0x -Wall -c expression.cpp

user.o: user.hpp user.cpp
	g++ -std=c++0x -Wall -c user.cpp

menu.o: menu.hpp menu.cpp
	g++ -std=c++0x -Wall -c menu.cpp

start.o: start.hpp start.cpp expression_factory.o
	g++ -std=c++0x -Wall -c start.cpp expression_factory.o

expression_factory.o: expression_factory.hpp expression_factory.cpp
	g++ -std=c++0x -Wall -c expression_factory.cpp

new_user.o: new_user.hpp new_user.cpp
	g++ -std=c++0x -Wall -c new_user.cpp

util.o: util.hpp util.cpp
	g++ -std=c++0x -Wall -c util.cpp

clean:
	$(RM) main $(OBJS)
