all:redblack

objects = red_black.o treenav.o parser.h

redblack: red_black.cpp treenav.cpp parser.cpp queue.cpp torun.cpp
	g++ -pthread -o redblack red_black.cpp treenav.cpp parser.cpp queue.cpp torun.cpp -I -Wall -ggdb3

.PHONY : clean
clean: 
	-rm $(objects)
