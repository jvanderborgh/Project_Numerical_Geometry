CC=gcc
CFLAGS=-Wall -Werror -O3
LDFLAGS=-lm 
# -lm rajoute les librairies standars par exemple mais ya moyen d'en ajouter d'autres Google est ton ami :-)
EXEC=./exec
SRC= $(wildcard *.c) 
#SOURCES
OBJ= $(SRC:.c=.o)
#OBJETS

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

reader_writer.o: reader_writer.c reader_writer.h
	$(CC) -o $@ -c $< $(CFLAGS)

#monfichier.o: monfichier.c dependence1.h dependence2.h
#	$(CC) -o $@ -c $< $(CFLAGS)

run: all
	$(EXEC)

gmsh: 
	open ./Out/triangle.out

coucou:
	echo coucou

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
