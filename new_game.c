#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME_STR_LEN 40

typedef struct game_settings {
  char  **board, player1[NAME_STR_LEN], player2[NAME_STR_LEN], *curr_player,
        play_col;
  int nrows, ncol, play_row, num_play, new_rule_p1, new_rule_p2;
} Board;

typedef struct game_play {
    char **board, player[NAME_STR_LEN], play_col;
    int nrows, ncol, play_row, new_rule_tag;
    struct game_play * next;
} play_t;

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

void set_rules(Board * settings)
{
  char confirmation='n';

  printf("Player 1, please insert your name: ");
  scanf("%s", settings->player1);
  printf("Player 2, please insert your name: ");
  scanf("%s", settings->player2);

  settings->curr_player = settings->player1;

  do {
    printf("\t%s, insert the size of the game board.\nLines: ",
           settings->player1);
    scanf("%d", &(settings->nrows));
    printf("Columns: ");
    scanf("%d", &(settings->ncol));
    getchar();

    if(settings->ncol > settings->nrows) {
      if(settings->nrows < 4 || settings->nrows > 8)
        if(settings->ncol < 6 || settings->ncol > 10) {
          printf("\nGame board size invalid! Number of columns and rows"
                 " invalid!\nPress any key to continue");
          getchar();
        } else {
          printf("\nGame board size invalid! Number of rows invalid!\n"
                 "Press any key to continue");
          getchar();
        }
      else
          if(settings->ncol < 6 || settings->ncol > 10) {
            printf("\nGame board size invalid! Number of columns invalid!\n"
                   "Press any key to continue");
            getchar();
          } else {
            printf("\n\t%s, do you agree with the game board size? (Y/N) ",
               settings->player2);
            do {

              scanf("%c", &confirmation);
               getchar();
          } while(confirmation != 'Y' && confirmation != 'y'
                  && confirmation != 'N' && confirmation != 'n');
          }
    } else {
      printf("Number of columns is less than number of rows.\n"
             "Press any key to continue");
      getchar();
    }
  } while((confirmation!='y' && confirmation!='Y')
			|| settings->nrows < 4 || settings->nrows > 8 || settings->ncol < 6
      || settings->ncol > 10 || settings->ncol < settings->nrows);

  settings->num_play = 0;
  settings->new_rule_p1 = 0;
  settings->new_rule_p2 = 0;
}

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

int validation(Board * settings, int play_row, int play_col, int *keep_play)
{
  if(play_row >= 0 && play_row < settings->nrows && play_col >= 0 &&
     play_col < settings->ncol)
    if(get_pos(settings, play_row, play_col) == 'X') {
      *keep_play = 0;
      return 0;
    } else
        if(get_pos(settings, play_row, play_col) == ' ')
          return 1;
        else
          return 0;
  else
    return 1;
}

void play(Board *settings, int *keep_play)
{
  int end_row, end_col, i, j;

  do {
    printf("%s, your turn to play (c/l): ", settings->curr_player);
    scanf(" %c %d", &(settings->play_col), &(settings->play_row));

    end_row = settings->play_row - 1;
    end_col = settings->play_col - 'A';
  }while(validation(settings, end_row, end_col, keep_play));

  settings->num_play++;

  for(i = 0; i <= end_row; i++)
    for(j = 0; j <= end_col; j++)
      settings->board[i][j] = ' ';
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

void change_player(Board *settings)
{
      if(!strcmp(settings->curr_player, settings->player1))
        settings->curr_player = settings->player2;
      else
        settings->curr_player = settings->player1;
}

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

void menu_game(Board settings, int *option)
{

    printf("\n%s, your turn to play:\n\n1. New Play\n2. Increase gameboard size\n"
           "3. Play history\n4. Save and quit game\nOption: "
           , settings.curr_player);
  do {
    scanf("%d", option);
    getchar();
    if(*option < 1 || *option > 4)
      printf("Invalid Option!\nOption: ");
  }while(*option < 1 || *option > 4);
}

void game_players()
{
  Board settings;
  play_t *head = NULL;
  int keep_play = 1, option;

  set_rules(&settings);
  create_board(&settings);

  do {
    print_board(settings);
    menu_game(settings, &option);

    switch(option)
    {
      case 1:
        play(&settings, &keep_play);
        add_play(&settings, &head);
        change_player(&settings);
        break;

      case 2:
        validation_new_rule(&settings);
        break;

      case 3:
        play_history(head);
        break;

      case 4:
        save_game(&settings, head);
        keep_play = 0;
        break;

      default:
        printf("Invalid Option!\nPress any key to continue.");
        getchar();
        break;
    }
  } while(keep_play);

  if(option == 1)
    printf("%s, you won!\n", settings.curr_player);

  save_file(head);
  free_game_mem(&settings, &head);
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

void restart_game()
{
  Board settings;
  play_t *head = NULL;
  int keep_play = 1, option;

  load_game(&settings, &head);

  do {
    print_board(settings);
    menu_game(settings, &option);

    switch(option)
    {
      case 1:
        play(&settings, &keep_play);
        add_play(&settings, &head);
        change_player(&settings);
        break;

      case 2:
        validation_new_rule(&settings);
        break;

      case 3:
        play_history(head);
        break;

      case 4:
        save_game(&settings, head);
        keep_play = 0;
        break;

      default:
        printf("Invalid Option!\nPress any key to continue.");
        getchar();
        break;
    }
  } while(keep_play);

  if(option == 1)
    printf("%s, you won!\n\n", settings.curr_player);

  save_file(head);
  free_game_mem(&settings, &head);
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
      case 1:
        game_players();
        break;

      case 2:
        printf("Load last game\n");
        restart_game();
        break;

      case 3:
        printf("Autor: Guilherme José Rodrigues Garrucho 21230252"
               "\nPress any key to continue. ");
        getchar();
        break;

      case 4:
        printf("Are you sure? (Y/N)");
        scanf("%c", &confirmation);
        break;

      default:
        printf("Invalid option!\nPress any key to continue!");
        getchar();
        printf("\n\n");
        break;
    }
  } while((confirmation != 'Y' && confirmation != 'y') || option != 4);
}

int main(void)
{
  menu();
  return 0;
}
