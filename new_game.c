#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME_STR_LEN 40

typedef struct game_board {
  char **board, player1[NAME_STR_LEN], player2[NAME_STR_LEN], *curr_player, play_col;
  int nrows, ncol, play_row;
} Board;

typedef struct game_board_play {
    char **board;
    char player[NAME_STR_LEN];
    int nrows, ncol, play_row, play_col;
    struct game_board_play * next;
} play_t;

play_t *head = NULL;

void save_file(play_t * head, char *player)
{

}

void play_history(play_t *new_play)
{
  int i, j;
  play_t * curr = new_play;
  int num_play = 1;
  if(curr != NULL)
    while(curr != NULL) {
      printf("Play number %d\n", num_play++);
      printf("\t\t|");
      for(i = 0, j = 'A';i < new_play->ncol; i++)
        printf(" %c |", j++);

      for(i = 0;i < new_play->nrows; i++)
        for(j = 0; j < new_play->ncol; j++) {
          if(!j)
            printf("\n\t   | %2d |", i+1);
          printf(" %c |", new_play->board[i][j]);
        }
      putchar('\n');
      curr = curr->next;
  }
  else
    printf("There's no plays yet!\n");
}

void board_copy(Board game_board, play_t *new_play)
{
  int i, j;

  new_play->nrows = game_board.nrows;
  new_play->ncol = game_board.ncol;

  new_play->board = malloc(new_play->nrows * sizeof(char *));
  for(i = 0; i < new_play->nrows; i++)
    new_play->board[i] = malloc(new_play->ncol * sizeof(char));

  for(i = 0; i < game_board.nrows; i++)
    for(j = 0; j < game_board.ncol; j++)
      new_play->board[i][j] = game_board.board[i][j];

  strcpy(new_play->player, game_board.curr_player);
}

void add_play(Board game_board, play_t ** head)
{
  play_t * curr;
  printf("curr %p \nhead %p\n", curr, head);
  play_t * new_play = (play_t *) malloc(sizeof(play_t));

  board_copy(game_board, new_play);

  new_play->next = NULL;

  if(curr == NULL)
    curr = new_play;
  else
      while(curr->next != NULL) {
        curr = curr->next;

      curr->next = new_play;
      curr->next->next = NULL;
    }
}

void set_rules(Board *game_board)
{
  char confirmation='n';

  printf("Player 1, please insert your name: ");
  scanf("%s", game_board->player1);
  printf("Player 2, please insert your name: ");
  scanf("%s", game_board->player2);

  game_board->curr_player = game_board->player1;

  do {
    printf("\t%s, insert the size of the game board.\nLines: ",
           game_board->player1);
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
                 game_board->player2);
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

void play(Board *game_board, int *keep_play)
{
  int end_row, end_col, i, j;

  do {
    printf("%s, your turn to play (c/l): ", game_board->curr_player);
    scanf(" %c %d", &(game_board->play_col), &(game_board->play_row));

    end_row = game_board->play_row - 1;
    end_col = game_board->play_col - 'A';
  } while(validation(game_board, end_row, end_col, keep_play));

  for(i = 0; i <= end_row; i++)
    for(j = 0; j <= end_col; j++)
      game_board->board[i][j] = ' ';
}

void menu_game(int *option)
{
  printf("1. New Play\n2. Play history\n");
  scanf("%d", option);
}

void change_player(Board *settings)
{
      if(!strcmp(settings->curr_player, settings->player1))
        settings->curr_player = settings->player2;
      else
        settings->curr_player = settings->player1;
}

void game()
{
  Board settings;
  int keep_play = 1, option;

  set_rules(&settings);
  create_board(&settings);

  print_board(settings);
  do {
    menu_game(&option);

    if(option == 1) {
      play(&settings, &keep_play);
      add_play(settings, &head);
      print_board(settings);
      change_player(&settings);
    } else {
      play_history(head);
    }
  } while(keep_play);

  printf("%s, you won!\n", settings.curr_player);

  //TODO save play to file
  free_board(&settings);
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
