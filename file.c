#include "file.h"
#include "board.h"

void save_game(Board * settings, play_t * head)
{
  FILE * settings_file;
  play_t * curr = head;
  int i;

  settings_file = fopen("last_settings.dat", "wb");

  fwrite(settings, sizeof (Board), 1, settings_file);

  for(i = 0; i < settings->nrows; i++)
    fwrite(settings->board[i], sizeof (char), settings->ncol, settings_file);

  while(curr != NULL) {
    fwrite(curr, sizeof (play_t), 1, settings_file);
    for(i = 0; i < curr->nrows; i++)
      fwrite(curr->board[i], sizeof (char), curr->ncol, settings_file);
    curr = curr->next;
  }

  fclose(settings_file);
}

void save_file(play_t * head)
{
  FILE * last_game;
  play_t * curr = head;
  int num_play1 = 1, num_play2 = 1, num_play = 1, *num_player_play, i, j;

  num_player_play = &num_play1;
  last_game = fopen("last_game.txt", "wt");

  if(last_game == NULL) {
    printf("Error creating file!\n");
    return;
  }

  while(curr != NULL) {
    if(curr->new_rule_tag == 1)
      fprintf(last_game, "%dº play: %s's %dº play -> Increased board size."
              "%c %d\n", num_play++, curr->player, (*num_player_play)++,
              curr->play_col, curr->play_row);
    else
      fprintf(last_game, "%dº play: %s's %dº play -> %c %d\n", num_play++,
            curr->player, (*num_player_play)++, curr->play_col, curr->play_row);

    fprintf(last_game, "\t\t|");

    for(i = 0, j = 'A'; i < curr->ncol; i++)
      fprintf(last_game, " %c |", j++);

    for(i = 0; i < curr->nrows; i++)
      for(j = 0; j < curr->ncol; j++) {
        if(!j)
          fprintf(last_game, "\n\t   | %2d |", i+1);
        fprintf(last_game, " %c |", curr->board[i][j]);
      }

    fprintf(last_game, "\n\n");

    if(num_play2 < num_play1)
      num_player_play = &num_play2;
    else
      num_player_play = &num_play1;

    curr = curr->next;
    }
  fclose(last_game);
}

void load_settings(FILE * old_settings, Board * settings, play_t ** head )
{
  play_t * curr, * aux;
  int i, j;

  fread(settings, sizeof (Board), 1, old_settings);
  create_board(settings);

  for(i = 0; i < settings->nrows; i++)
    fread(settings->board[i], sizeof (char), settings->ncol, old_settings);

  *head = (play_t *) malloc(sizeof (play_t));
  curr = *head;

  for(i = 0; i < settings->num_play; i++) {
    fread(curr, sizeof (play_t), 1, old_settings);

    curr->board = malloc(curr->nrows * sizeof (char *));
    for(j = 0; j < curr->nrows; j++)
      curr->board[j] = malloc(curr->ncol * sizeof (char));

    for(j = 0; j < curr->nrows; j++)
      fread(curr->board[j], sizeof (char), curr->ncol, old_settings);

    aux = curr;
    curr->next = malloc(sizeof (play_t));
    curr = curr->next;

  }
  free(curr);
  aux->next = NULL;
}

void load_game(Board * settings, play_t **head)
{
  FILE * old_settings;
  play_t * curr;

  old_settings = fopen("last_settings.dat", "rb");
  if(old_settings == NULL) {
    printf("Error creating file!\n");
    return;
  }
  load_settings(old_settings, settings, head);

  curr = *head;
  while(curr->next !=NULL)
    curr = curr->next;

  if(!strcmp(curr->player, settings->player1))
    settings->curr_player = settings->player2;
  else
    settings->curr_player = settings->player1;

  fclose(old_settings);
}
