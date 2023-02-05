# Standard compiler variables
CC = g++
CCFLAGS = -Wall -g

# Rules start here

z1863905_project1: z1801624_project1.o
	$(CC) -o z1801624_project1 $(CCFLAGS) z1801624_project1.o

z1801624_project1.o: z1801624_project1.cc
	$(CC) -c $(CCFLAGS) z1801624_project1.cc

clean:
	-rm *.o z1801624_project1
