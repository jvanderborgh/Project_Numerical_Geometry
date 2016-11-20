CC=gcc
CFLAGS=-Wall -Werror
LDFLAGS=

EXEC=./exec
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)


all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c reader_writer.h
	$(CC) -o $@ -c $< $(CFLAGS)

run: all
	$(EXEC)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
