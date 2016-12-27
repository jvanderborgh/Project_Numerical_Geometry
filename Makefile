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

functions_nous.o: functions_nous.cpp struct.h
	$(CC) -o $@ -cpp $< $(CFLAGS)
functions_prof.o: functions_prof.cpp struct.h functions_prof.h robustPredicates.h
	$(CC) -o $@ -cpp $< $(CFLAGS)
robustPredicates.o: robustPredicates.cpp
	$(CC) -o $@ -cpp $< $(CFLAGS)


#DT.o: DT.cpp DT.h
#	$(CC) -o $@ -cpp $< $(CFLAGS)

main.o: main.cpp struct.h functions_prof.h functions_nous.h robustPredicates.h
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