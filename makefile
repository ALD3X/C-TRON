CC = gcc
CFLAGS = -Wall

SRC = main.c $(wildcard ./controlleur/*.c ./modele/*.c ./vue/*.c)

OBJ = $(SRC:.c=.o)

EXEC = TronGame

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(EXEC)
