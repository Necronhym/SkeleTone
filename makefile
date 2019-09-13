INPUT=c.cpp
OUTPUT=Skeletone
FLAGS=-o
LINKS= -lSDL2
CC=g++
c: $(INPUT)
	$(CC) $(INPUT) $(FLAGS) $(OUTPUT) $(LINKS)
