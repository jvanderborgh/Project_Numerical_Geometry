CC=gcc
CFLAGS=-Wall -Werror -O3
LDFLAGS=-lm 
# -lm rajoute les librairies standards par exemple mais ya moyen d'en ajouter d'autres Google est ton ami :-)
EXEC=./exec
SRC= $(wildcard *.c) 
#SOURCES
OBJ= $(SRC:.c=.o)
#OBJETS

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

reader_writer.o: reader_writer.cpp reader_writer.h delaunay.h
	$(CC) -o $@ -cpp $< $(CFLAGS)

#monfichier.o: monfichier.c dependence1.h dependence2.h
#	$(CC) -o $@ -c $< $(CFLAGS)

run: all
	$(EXEC)

gmsh: 
	open ./Out/triangle.out

hilbert:
	open ./Out/hilbert.out

coucou:
	echo coucou

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
