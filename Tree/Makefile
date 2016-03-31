.PHONY : clean
.PHONY : oclean
#CC=gcc
CXXFLAGS=-c -Wextra -g -Wall

all: tree

tree: main.o tree.o stack.o
	$(CC) *.o -o $@ -g -Wextra

main.o: main.c
	$(CC) $(CXXFLAGS) main.c 

tree.o: tree.c
	$(CC) $(CXXFLAGS) tree.c

stack.o: stack.c
	$(CC) $(CXXFLAGS) stack.c

clean:
	rm -rf *.o tree
oclean:
	rm -rf *.o
