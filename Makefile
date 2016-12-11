OBJS = expression.o expression_factory.o user.o menu.o start.o new_user.o highscores.o util.o

main: main.cpp $(OBJS)
	g++ -std=c++0x -Wall -o main main.cpp $(OBJS)

start.o: start.hpp start.cpp expression_factory.o menu.o user.o util.o expression.o expression_factory.o
	g++ -std=c++0x -Wall -c start.cpp expression_factory.o

new_user.o: new_user.hpp new_user.cpp menu.o user.o util.o
	g++ -std=c++0x -Wall -c new_user.cpp

highscores.o: highscores.hpp highscores.cpp menu.o user.o util.o
	g++ -std=c++0x -Wall -c highscores.cpp

util.o: util.hpp util.cpp user.o
	g++ -std=c++0x -Wall -c util.cpp

user.o: user.hpp user.cpp
	g++ -std=c++0x -Wall -c user.cpp

menu.o: menu.hpp menu.cpp
	g++ -std=c++0x -Wall -c menu.cpp

expression_factory.o: expression_factory.hpp expression_factory.cpp expression.o
	g++ -std=c++0x -Wall -c expression_factory.cpp

expression.o: expression.hpp expression.cpp
	g++ -std=c++0x -Wall -c expression.cpp

clean:
	$(RM) main $(OBJS)
