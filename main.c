#include <stdio.h>
#define NAME_STR_LEN 40

int printboard(char *board, int columns, int lines)
{
	int i;
	for(i = 0; i < columns*lines; i++)
	{
		if(i % columns == 0)
			printf("\n|");
		printf(" %c |", *(board+i));
	}
	putchar('\n');
	return 0;
}

int validation(char *board, int x, int y, int columns, int lines)
{
		if(*(board+x*columns+y*lines)==' ')
			return 1;
		else
			return 0;
/*	else
		if(*(board+x+y)=='X')
			return 0;
		else
			return 1;
			*/
}
//int play(char *board, char *player1, char *player2, int columns, int lines)

int gameplay(char *board, char *player1, char *player2, int columns, int lines)
{
	int win=1, x, y, i, j;
	char *winner;
	system("clear");
	do
	{
		do
		{
			printf("%s, your turn to play (c/l): ", player1);
			scanf("%d %d", &x, &y);
		}
		while(validation(board, x, y, columns, lines));
		if(validation(board, x, y, columns, lines))
		{
			winner=player2;
			win=0;
			break;
		}
		for(i=0;i<x;i++)
			for(j=0;j<y;j++)
				*(board+i*columns+j*lines)=' ';
		printboard(board, columns, lines);
		getchar();

		do
		{
			printf("%s, your turn to play: ", player2);
			scanf("%d %d", &x, &y);
		}
		while(validation(board, x, y, columns, lines));
		if(validation(board, x, y, columns, lines))
		{
			winner=player1;
			win=0;
			break;
		}
		for(i=0;i<x;i++)
			for(j=0;j<y;j++)
				*(board+i*columns+j*lines)=' ';
		printboard(board, columns, lines);
	} while(win);
	getchar();
	printf("%s you have won the game!\n", *winner);
	return 0;
}

int initializeboard(char *board, int columns, int lines)
{
	int i;
	for(i=0;i < columns*lines; i++)
	{
		*(board+i)='*';
		if(i==columns*lines-1)
			*(board+i)='X';
	}
	return 1;
}

int createboard(char *player1, char *player2, int *columns, int *lines)
{
	char confirmation='n';

		printf("Player 1, please insert your name: ");
		scanf("%s", player1);
		printf("Player 2, please insert your name: ");
		scanf("%s", player2);

	do {
		system("clear");

		printf("\t%s, please insert the size of the game board.\nColumns: ", player1);
		scanf("%d", columns);

		printf("Lines: ");
		scanf("%d", lines);
		getchar();

		if(*lines < 4 || *lines > 8)
			if(*columns < 6 || *columns > 10)
			{
				printf("\nGame board size invalid! Number of columns and lines invalid!\n");
				printf("Press any key to continue!");
				getchar();
			}
			else
			{
				printf("\nGame board size invalid! Number of lines invalid!\n");
				printf("Press any key to continue!");
				getchar();
			}
		else
			if(*columns < 6 || *columns > 10)
			{
				printf("\nGame board size invalid! Number of columns invalid!\n");
				printf("Press any key to continue!");
				getchar();
			}
			else
			{
				printf("\n\t%s, do you agree with the game board size? (Y/N)", player2);
				scanf("%c", &confirmation);
				getchar();
			}
	}
	while(confirmation!='y' && confirmation!='Y' || *lines < 4 || *lines > 8 || *columns < 6 || *columns > 10);

	return 0;
}

int game()
{
	char player1[NAME_STR_LEN], player2[NAME_STR_LEN];
	int columns, lines;
	createboard(player1, player2, &columns, &lines);

	char board[columns][lines];
	initializeboard(*board, columns, lines);

	printboard(*board, columns, lines);
	getchar();

	gameplay(*board, player1, player2, columns, lines);
	getchar();
	return 0;
}

int menu()
{
	int option;
	char confirmation;

	do
	{
		system("clear");

		printf("\t1. New Game\n\t2. Load Last Game\n\t3. Credits\n\t4. Quit Game\n\nOption: ");
		scanf("%d", &option);
		getchar();

		switch(option)
		{
			case 1: game(); break;
			case 2: printf("Load last game!\n"); break;
			case 3: printf("Autor: Guilherme José Rodrigues Garrucho 21230252\nPress any key to continue!"); getchar(); break;
			case 4: printf("Are you sure? (Y/N)"); scanf("%c", &confirmation); break;
			default: printf("Invalid option!\nPress any key to continue!"); getchar();
		}

	}
	while(confirmation!='Y' && confirmation!='y' || option!=4);

	return 0;
}

int main()
{
	menu();
	return 0;
}
