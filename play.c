#include "play.h"

void play_history(play_t * head)
{
  int i, j;
  play_t * curr = head;
  int num_play = 1, num_play1 = 1, num_play2 = 1, *num_player_play;

  num_player_play = &num_play1;

  if(curr != NULL)
    while(curr != NULL) {
      if(curr->new_rule_tag == 1)
        printf("%dª play: %s's %dª play -> Increased Board Size. %c %d \n",
              num_play++, curr->player, (*num_player_play)++, curr->play_col,
              curr->play_row);
      else
        printf("%dª play: %s's %dª play -> %c %d\n", num_play++, curr->player,
              (*num_player_play)++, curr->play_col, curr->play_row);

      printf("\t\t|");
      for(i = 0, j = 'A';i < curr->ncol; i++)
        printf(" %c |", j++);

      for(i = 0;i < curr->nrows; i++)
        for(j = 0; j < curr->ncol; j++) {
          if(!j)
            printf("\n\t   | %2d |", i+1);
          printf(" %c |", curr->board[i][j]);


      if(num_play2 < num_play1)
        num_player_play = &num_play2;
      else
        num_player_play = &num_play1;
        }
      putchar('\n');
      curr = curr->next;
  }
  else
    printf("There's no plays yet!\n");
}

void board_copy(Board * settings, play_t * new_play)
{
  int i, j;

  new_play->play_row = settings->play_row;
  new_play->play_col = settings->play_col;
  new_play->nrows = settings->nrows;
  new_play->ncol = settings->ncol;

  new_play->board = malloc(new_play->nrows * sizeof(char *));
  for(i = 0; i < new_play->nrows; i++)
    new_play->board[i] = malloc(new_play->ncol * sizeof(char));

  for(i = 0; i < settings->nrows; i++)
    for(j = 0; j < settings->ncol; j++)
      new_play->board[i][j] = settings->board[i][j];

  strcpy(new_play->player, settings->curr_player);

  if(!strcmp(settings->curr_player, settings->player1))
    if(settings->new_rule_p1 == 1) {
      new_play->new_rule_tag = 1;
      settings->new_rule_p1 = -1;
    }
    else
      new_play->new_rule_tag = 0;
  else
    if(settings->new_rule_p2 == 1) {
      new_play->new_rule_tag = 1;
      settings->new_rule_p2 = -1;
    }
    else
      new_play->new_rule_tag = 0;

  new_play->next = NULL;
}

void add_play(Board * settings, play_t ** head)
{
  play_t * curr = *head;
  play_t * new_play = (play_t *) malloc(sizeof(play_t));

  board_copy(settings, new_play);

  if(*head == NULL)
    *head = new_play;
  else {
      while(curr->next != NULL)
        curr = curr->next;
      curr->next = new_play;
    }
}
