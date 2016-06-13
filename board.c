#include "board.h"

void create_board(Board * settings)
{
  int i, j;

  settings->board = malloc(settings->nrows * sizeof(char *));
  for(i = 0;i < settings->nrows; i++)
    settings->board[i] = malloc(settings->ncol * sizeof(char));

  for(i = 0;i < settings->nrows; i++)
    for(j = 0;j < settings->ncol; j++) {
      settings->board[i][j] = '*';
      if(i == settings->nrows - 1 && j == settings->ncol - 1)
        settings->board[i][j] = 'X';
    }
}

void free_game_mem(Board *settings, play_t ** head)
{
  int i;
  play_t * curr = * head, * aux;

  for(i = 0; i < settings->nrows; i++)
    free(settings->board[i]);
  free(settings->board);

  while(curr != NULL) {
    aux = curr->next;
    curr->next = NULL;

    for(i = 0; i < curr->nrows; i++)
      free(curr->board[i]);
    free(curr->board);

    free(curr);
    curr = aux;
  }
}

void print_board(Board settings)
{
  int i, j;

  printf("\n\n\t\t|");
  for(i = 0, j = 'A';i < settings.ncol; i++)
    printf(" %c |", j++);

  for(i = 0;i < settings.nrows; i++)
    for(j = 0; j < settings.ncol; j++) {
      if(!j)
        printf("\n\t   | %2d |", i+1);
      printf(" %c |", settings.board[i][j]);
    }
  putchar('\n');
}

int get_pos(Board * settings, int play_row, int play_col)
{
  return settings->board[play_row][play_col];
}

void validation_new_rule(Board * settings)
{
  if(!strcmp(settings->curr_player, settings->player1))
    if(settings->new_rule_p1 == 0)
      new_rule(settings);
    else {
      printf("You've already increased the board.\nPress any key to continue\n");
      getchar();
      printf("\n\n");
    }
  else
    if(settings->new_rule_p2 == 0)
      new_rule(settings);
    else {
        printf("You've already increased the board.\nPress any key to continue\n");
        getchar();
        printf("\n\n");
      }
}

void new_rule(Board * settings)
{
  int i;

    settings->board[settings->nrows - 1][settings->ncol - 1] = '*';
    settings->nrows++;
    settings->ncol++;

    settings->board = realloc (settings->board ,
                               settings->nrows * sizeof (char *));
    for(i = 0; i < settings->nrows; i++)
      settings->board[i] = realloc(settings->board[i],
                                   settings->ncol * sizeof (char));

    for(i = 0; i < settings->ncol; i++)
      settings->board[settings->nrows - 1][i] = '*';

    for(i = 0; i < settings->nrows; i++)
      settings->board[i][settings->ncol - 1] = '*';

    settings->board[settings->nrows - 1][settings->ncol - 1] = 'X';

    if(!strcmp(settings->curr_player, settings->player1))
        settings->new_rule_p1++;
    else
        settings->new_rule_p2++;
}
