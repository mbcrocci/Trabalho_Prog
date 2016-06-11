#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME_STR_LEN 40

typedef struct game_board {
  char  **board, player1[NAME_STR_LEN], player2[NAME_STR_LEN], *curr_player,
        play_col;
  int nrows, ncol, play_row, num_play;
} Board;

typedef struct game_board_play {
    char **board, player[NAME_STR_LEN], play_col;
    int nrows, ncol, play_row;
    struct game_board_play * next;
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

void play_history(play_t *head)
{
  int i, j;
  play_t * curr = head;
  int num_play = 1, num_play1 = 1, num_play2 = 1, *num_player_play;

  num_player_play = &num_play1;

  if(curr != NULL)
    while(curr != NULL) {
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

void board_copy(Board game_board, play_t *new_play)
{
  int i, j;

  new_play->play_row = game_board.play_row;
  new_play->play_col = game_board.play_col;
  new_play->nrows = game_board.nrows;
  new_play->ncol = game_board.ncol;

  new_play->board = malloc(new_play->nrows * sizeof(char *));
  for(i = 0; i < new_play->nrows; i++)
    new_play->board[i] = malloc(new_play->ncol * sizeof(char));

  for(i = 0; i < game_board.nrows; i++)
    for(j = 0; j < game_board.ncol; j++)
      new_play->board[i][j] = game_board.board[i][j];

  strcpy(new_play->player, game_board.curr_player);
  new_play->next = NULL;
}

void add_play(Board game_board, play_t ** head)
{
  play_t * curr = *head;
  play_t * new_play = (play_t *) malloc(sizeof(play_t));

  board_copy(game_board, new_play);

  if(*head == NULL)
    *head = new_play;
  else {
      while(curr->next != NULL)
        curr = curr->next;
      curr->next = new_play;
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
			|| game_board->nrows < 4 || game_board->nrows > 8 || game_board->ncol < 6
      || game_board->ncol > 10 || game_board->ncol < game_board->nrows);
  game_board->num_play = 0;
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

  printf("\n\n\t\t|");
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

  game_board->num_play++;
  printf("Num play = %d\n", game_board->num_play);
  for(i = 0; i <= end_row; i++)
    for(j = 0; j <= end_col; j++)
      game_board->board[i][j] = ' ';
}

void menu_game(Board settings, int *option)
{
  printf("%s, your turn to play:\n\n1. New Play\n2. Play history\n"
         "3. Save and quit game\n", settings.curr_player);
  scanf("%d", option);
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
        add_play(settings, &head);
        print_board(settings);
        change_player(&settings);
        break;
      case 2:
        play_history(head);
        break;
      case 3:
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
  free_board(&settings);
}

void load_settings(FILE * old_settings, Board * settings, play_t ** head )
{
  play_t * curr, * play_node;
  int i, j;

  fread(settings, sizeof (Board), 1, old_settings);
  create_board(settings);

  for(i = 0; i < settings->nrows; i++)
    fread(settings->board[i], sizeof (char), settings->ncol, old_settings);

  *head = (play_t *) malloc(sizeof (play_t));
  curr = *head;

  fread(curr, sizeof (play_t), 1, old_settings);

  curr->board = malloc(curr->nrows * sizeof(char *));
  for(i = 0; i < curr->nrows; i++)
    curr->board[i] = malloc(curr->ncol * sizeof(char));

  for(i = 0; i < curr->nrows; i++)
    fread(curr->board[i], sizeof (char), curr->ncol, old_settings);


  for(i = 1; i < settings->num_play; i++) {
    play_node = (play_t *) malloc(sizeof (play_t));
    fread(play_node, sizeof (play_t), 1, old_settings);

    play_node->board = malloc(play_node->nrows * sizeof (char *));
    for(j = 0; j < play_node->nrows; j++)
      play_node->board[i] = malloc(play_node->ncol * sizeof(char));

    for(j = 0; j < play_node->nrows; j++)
      fread(play_node->board[i], sizeof (char), play_node->ncol, old_settings);

    curr->next = play_node;
    curr = play_node;
  }

  curr->next = NULL;

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
    settings->curr_player = settings->player1;
  else
    settings->curr_player = settings->player2;

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
        add_play(settings, &head);
        print_board(settings);
        change_player(&settings);
        break;
      case 2:
        play_history(head);
        break;
      case 3:
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
      case 1: game_players();
              break;
      case 2: printf("Load last game\n");
              restart_game();
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
