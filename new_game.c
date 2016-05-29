#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME_STR_LEN 40

typedef struct game_board {
  char **board;
  int nrows, ncol;
} Board;

void set_rules(char *player1, char *player2, Board *game_board)
{
  char confirmation='n';

  printf("Player 1, please insert your name: ");
  scanf("%s", player1);
  printf("Player 2, please insert your name: ");
  scanf("%s", player2);

  do {
    printf("\t%s, insert the size of the game board.\nLines: ", player1);
    scanf("%d", &(game_board->nrows));
    printf("Columns: ");
    scanf("%d", &(game_board->ncol));
    getchar();

    if(game_board->ncol > game_board->nrows) {
      if(game_board->nrows < 4 || game_board->nrows > 8)
        if(game_board->ncol < 6 || game_board->ncol > 10) {
          printf("\nGame board size invalid! Number of columns and rows"
                  " invalid!\nPress any key to continue");
          getchar();
        } else {
          printf("\nGame board size invalid! Number of rows invalid!\n"
                 "Press any key to continue");
          getchar();
        }
      else
          if(game_board->ncol < 6 || game_board->ncol > 10) {
            printf("\nGame board size invalid! Number of columns invalid!\n"
                   "Press any key to continue");
            getchar();
          } else {
          printf("\n\t%s, do you agree with the game board size? (Y/N) ",
                 player2);
          scanf("%c", &confirmation);
          getchar();
          }
    } else {
      printf("Number of columns is less than number of rows.\n"
             "Press any key to continue");
      getchar();
    }
  } while((confirmation!='y' && confirmation!='Y')
			|| game_board->nrows < 4 || game_board->nrows > 8 || game_board->ncol < 6 || game_board->ncol > 10
      || game_board->ncol < game_board->nrows);
}

void create_board(Board *game_board)
{
  int i, j;
  game_board->board = malloc(game_board->nrows * sizeof(char *));
  for(i = 0;i < game_board->nrows; i++)
    game_board->board[i] = malloc(game_board->ncol * sizeof(char));

  for(i = 0;i < game_board->nrows; i++)
    for(j = 0;j < game_board->ncol; j++) {
      game_board->board[i][j] = '*';
      if(i == game_board->nrows - 1 && j == game_board->ncol - 1)
        game_board->board[i][j] = 'X';
    }

}

void free_board(Board *game_board)
{
  int i;
  for(i = 0; i < game_board->nrows; i++)
    free(game_board->board[i]);
  free(game_board->board);
}

void print_board(Board game_board)
{
  int i, j;

  printf("\t\t|");
  for(i = 0, j = 'A';i < game_board.ncol; i++)
    printf(" %c |", j++);

  for(i = 0;i < game_board.nrows; i++)
    for(j = 0; j < game_board.ncol; j++) {
      if(!j)
        printf("\n\t   | %2d |", i+1);
      printf(" %c |", game_board.board[i][j]);
    }
  putchar('\n');
}

int get_pos(Board *game_board, int play_row, int play_col)
{
  return game_board->board[play_row][play_col];
}

int validation(Board *game_board, int play_row, int play_col, int *keep_play)
{
  if(play_row >= 0 && play_row < game_board->nrows && play_col >= 0 &&
     play_col < game_board->ncol)
    if(get_pos(game_board, play_row, play_col) == 'X') {
      *keep_play = 0;
      return 0;
    } else
      if(get_pos(game_board, play_row, play_col) == ' ')
        return 1;
      else
        return 0;
  else
    return 1;
}

void play(Board *game_board, char *player, int *keep_play)
{
  int play_row, end_row, end_col, i, j;
  char play_col;

  do {
    printf("%s, your turn to play (c/l): ", player);
    scanf(" %c %d", &play_col, &play_row);
    end_row = play_row - 1;
    end_col = play_col - 'A';
  } while(validation(game_board, end_row, end_col, keep_play));

  for(i = 0; i <= end_row; i++)
    for(j = 0; j <= end_col; j++)
      (game_board->board[i][j]) = ' ';

  //TODO save play to file
}

void game()
{
  Board game_board;
  char player1[NAME_STR_LEN], player2[NAME_STR_LEN], *curr_player = player1;
  int keep_play = 1;

  set_rules(player1, player2, &game_board);
  create_board(&game_board);

  print_board(game_board);
  do {

    play(&game_board, curr_player, &keep_play);
    print_board(game_board);

    if(!strcmp(curr_player, player1))
      curr_player = player2;
    else
      curr_player = player1;
  } while(keep_play);
  printf("%s, you won!\n", curr_player);

  free_board(&game_board);
}

void menu()
{
  int option;
  char confirmation;

  do {
    printf("\t1. New Game\n\t2. Load Last Game\n\t3. Credits\n\t4. Quit Game"
           "\nOption: ");
    scanf("%d", &option);
    getchar();

    switch(option) {
      case 1: game();
              break;
      case 2: printf("Load last game\n");
              getchar();
              break;
      case 3: printf("Autor: Guilherme José Rodrigues Garrucho 21230252"
                     "\nPress any key to continue. ");
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
}

int main(void)
{
  menu();
  return 0;
}
