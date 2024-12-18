CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -fopenmp -O3
SRC = src/*
OBJ = a.out
RM = rm -f

all: $(OBJ)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -o $(OBJ) $(SRC)

clean:
	$(RM) $(OBJ)
