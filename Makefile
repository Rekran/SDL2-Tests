CC = gcc

all:
	$(CC) main.c -I  -lSDL2main -lSDL2 -lSDL2_image -o game

clean:
	rm game

