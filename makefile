# MakeFile
game: main.c play.c file.c board.c 
	gcc -Wall -g -o game main.c play.c file.c board.c -I.
