#Blane Gorospe
#CSCI 480
CC = g++
CCFLAGS = -Wall -g

z1863905_project1: z1801624_project1.o
	$(CC) -o z1801624_project1 $(CCFLAGS) z1801624_project1.o

z1801624_project1.o: z1801624_project1.cpp
	$(CC) -c $(CCFLAGS) z1801624_project1.cpp

clean:
	-rm *.o z1801624_project1
