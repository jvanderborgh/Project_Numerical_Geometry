CC=g++
#gcc si on travaille avec c normal
#g++ si on fait des classes cpp
CFLAGS=-Wall -Werror -O3
LDFLAGS=-lm 
# -lm rajoute les librairies standards par exemple mais ya moyen d'en ajouter d'autres Google est ton ami :-)
EXEC=./exec
SRC= $(wildcard *.cpp) 
#SOURCES
OBJ= $(SRC:.c=.o)
#OBJETS

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

reader_writer.o: reader_writer.cpp reader_writer.h
	$(CC) -o $@ -cpp $< $(CFLAGS)

structures.o: structures.cpp structures.h
	$(CC) -o $@ -cpp $< $(CFLAGS)	

#DT.o: DT.cpp DT.h
#	$(CC) -o $@ -cpp $< $(CFLAGS)

main.o: main.cpp reader_writer.h robustPredicates.h structures.h
	$(CC) -o $@ -cpp $< $(CFLAGS)


#monfichier.o: monfichier.cpp dependence1.h dependence2.h
#	$(CC) -o $@ -cpp $< $(CFLAGS)

run: all
	$(EXEC)

gmsh: 
	open ./Out/Triangle.out

hilbert:
	open ./Out/Hilbert.out

square:
	open ./Out/Square.out

coucou:
	echo coucou

clean:
	rm -rf *.o ./Out/Hilbert.out ./Out/Triangle.out ./Out/Square.out

mrproper: clean
	rm -rf $(EXEC)
