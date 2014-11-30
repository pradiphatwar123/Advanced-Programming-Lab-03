#------------------------------------------------------------------------------

PROGRAM=unionfind
EXENAME=kruskal
CC=g++ -g

#------------------------------------------------------------------------------

all: $(PROGRAM)

$(PROGRAM):  main.o kruskal.o sort.o unionfind.o
	$(CC) main.o kruskal.o sort.o UnionFind.o -o $(EXENAME)

main.o: main.cpp globals.h
	$(CC) -c main.cpp 

kruskal.o: kruskal.cpp kruskal.h
	$(CC) -c kruskal.cpp

sort.o: sort.cpp sort.h
	$(CC) -c sort.cpp

unionfind.o: UnionFind.cpp UnionFind.h
	$(CC) -c UnionFind.cpp

clean:
	rm -f *.o *~  $(PROGRAM)


