#include <stdio.h>
#define NAME_STR_LEN 40

void printboard(char *board, int lines, int columns)
{
  int i, j;

  printf("\t\t|");
  for(i = 0, j = 'A'; i < columns; i++)
    printf(" %c |", j++);
  for(i = 0, j = 1; i < lines * columns; i++) {
    if(i % columns == 0)
      printf("\n\t   | %2d |", j++);
    printf(" %c |", *(board+i));
  }
  putchar('\n');
}

void initializeboard(char *board, int lines, int columns)
{
  int i;
  for(i = 0; i < lines * columns; i++)
  {
    *(board+i) = '*';
    if(i == columns * lines -1)
      *(board+i) = 'X';
  }
}

int createboard(char *player1, char *player2,  int *lines, int *columns)
{
  char confirmation='n';

  printf("Player 1, please insert your name: ");
  scanf("%s", player1);
  printf("Player 2, please insert your name: ");
  scanf("%s", player2);

  do {
    printf("\t%s, insert the size of the game board.\nLines: ", player1);
    scanf("%d", lines);
    printf("Columns: ");
    scanf("%d", columns);
    getchar();

    if(*columns > *lines)
      if(*lines < 4 || *lines > 8)
        if(*columns < 6 || *columns > 10) {
          printf("\nGame board size invalid! Number of columns and lines invalid!\nPress any key to continue");
          getchar();
        }
        else {
          printf("\nGame board size invalid! Number of lines invalid!\nPress any key to continue");
          getchar();
        }
        else
        if(*columns < 6 || *columns > 10) {
          printf("\nGame board size invalid! Number of columns invalid!\nPress any key to continue");
          getchar();
        }
        else {
          printf("\n\t%s, do you agree with the game board size? (Y/N) ", player2);
          scanf("%c", &confirmation);
          getchar();
        }
    else {
      printf("Number of columns is less than number of lines.\nPress any key to continue");
      getchar();
    }
  } while((confirmation!='y' && confirmation!='Y')
			|| *lines < 4 || *lines > 8 || *columns < 6 || *columns > 10 || *columns < *lines);
  return 0;
}

int validation_play(char *board, char *winner, char *player, int x, int y, int lines, int columns, int *lose)
{
  if(x > 0 && x <= lines && y > 0 && y <=columns)
    if(*(board + ( (x - 1) * columns + y ) - 1) == 'X') {
        winner = player;
        *lose = 0;
        return 0;
    }
    else
      if(*(board + ( ((x - 1) * columns) + y ) - 1) == ' ')
        return 1;
      else
        return 0;
  else
    return 1;
}

void play(char *board, char *player1, char *player2, int lines, int columns, char *player, char *winner, int *lose)
{
  int x, y, i, j;

  do {
    printf("%s, your turn to play (l/c): ", player);
    scanf("%d %d", &x, &y);
  } while(validation_play(board, player, winner, x, y, lines, columns, lose));

  for(i = 0; i < x; i++)
    for(j = 0; j < y;j++)
      if(*(board + i * columns + j) != 'X')
        *(board + i * columns + j) = ' ';
}

int game()
{
  char player1[NAME_STR_LEN], player2[NAME_STR_LEN], *winner = NULL;
  int lines, columns, lose = 1;

  createboard(player1, player2, &lines, &columns);

  char board[columns][lines];
  initializeboard(*board, lines, columns);
  printboard(*board, lines, columns);

  do {
    play(*board, player1, player2, lines, columns, player1, winner, &lose);
    printboard(*board, lines, columns);
    if(lose == 0)
      break;
    play(*board, player1, player2, lines, columns, player2, winner, &lose);
    printboard(*board, lines, columns);
  } while(lose);
  printf("%s, you are the winner!\n", winner);
  getchar();
  return 0;
}

int menu()
{
  int option;
  char confirmation;

  do {
    printf("\t1. New Game\n\t2. Load Last Game\n\t3. Credits\n\t4. Quit Game\nOption: ");
    scanf("%d", &option);
    getchar();

    switch(option) {
      case 1: game();
              break;
      case 2: printf("Load last game\n");
              getchar();
              break;
      case 3: printf("Autor: Guilherme José Rodrigues Garrucho 21230252\nPress any key to continue. ");
              getchar();
              break;
      case 4: printf("Are you sure? (Y/N)");
              scanf("%c", &confirmation);
              break;
      default:printf("Invalid option!\nPress any key to continue!");
              getchar();
              break;
    }
  } while((confirmation != 'Y' && confirmation != 'y') || option != 4);
  return 0;
}

int main(void) {
  menu();
  return 0;
}
