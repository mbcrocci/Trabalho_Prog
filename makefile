# MakeFile

CC=gcc

game: main.c play.c file.c board.c 
	$(CC) -Wall -g -o game main.c play.c file.c board.c -I.
