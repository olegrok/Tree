.PHONY : clean
.PHONY : oclean
#CC=gcc
CXXFLAGS=-c -Wextra -g -Wall -pedantic

all: tree

tree: main.o tree.o stack.o methods.o
	$(CC) *.o -o $@ -g -Wextra

main.o: main.c
	$(CC) $(CXXFLAGS) main.c

tree.o: tree.c
	$(CC) $(CXXFLAGS) tree.c

stack.o: stack.c
	$(CC) $(CXXFLAGS) stack.c
methods.o: methods.c
	$(CC) $(CXXFLAGS) methods.c

clean:
	rm -rf *.o tree
oclean:
	rm -rf *.o
