#include "main.h"
#include "file.h"
#include "play.h"
#include "board.h"

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
    printf("%s, your turn to play (c l): ", settings->curr_player);
    scanf(" %c %d", &(settings->play_col), &(settings->play_row));

    end_row = settings->play_row - 1;
    end_col = settings->play_col - 'A';
  }while(validation(settings, end_row, end_col, keep_play));

  settings->num_play++;

  for(i = 0; i <= end_row; i++)
    for(j = 0; j <= end_col; j++)
      settings->board[i][j] = ' ';
}

void change_player(Board *settings)
{
      if(!strcmp(settings->curr_player, settings->player1))
        settings->curr_player = settings->player2;
      else
        settings->curr_player = settings->player1;
}

void menu_game(Board settings, int *option)
{
  printf("\n%s, your turn to play:\n\n1. New Play\n2. Increase gameboard size"
           "\n3. Play history\n4. Save and quit game\nOption: "
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

  if(option == 1) {
    printf("%s, you won!\n", settings.curr_player);
    save_file(head);
  }

  free_game_mem(&settings, &head);
}

void restart_game_players()
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

  if(option == 1) {
    printf("%s, you won!\n", settings.curr_player);
    save_file(head);
  }

  free_game_mem(&settings, &head);
}

void set_rules_bot(Board * settings)
{
  printf("Player 1, please insert your name: ");
  scanf("%s", settings->player1);
  strcpy(settings->player2, "BOT");

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
            printf("BOT: Let's Play!\n\n");
          }
    } else {
      printf("Number of columns is less than number of rows.\n"
             "Press any key to continue");
      getchar();
    }
  } while(settings->nrows < 4 || settings->nrows > 8 || settings->ncol < 6 ||
          settings->ncol > 10 || settings->ncol < settings->nrows);

  settings->num_play = 0;
  settings->new_rule_p1 = 0;
  settings->new_rule_p2 = 0;
}

void init_random_gen()
{
  srand((unsigned) time(NULL));
}

int random_number(int min, int max)
{
  return min + rand() % (max - min + 1);
}

void play_bot(Board * settings, int *keep_play)
{
  char play_col;
  int i, j, play_row, play_new_rule;

  init_random_gen();

  play_new_rule = random_number(0, 1);
  if(play_new_rule == 1 && settings->new_rule_p2 == 0)
    new_rule(settings);

  do {
    play_col = random_number(0, settings->ncol - 1);
    play_row = random_number(0, settings->nrows - 1);
  }while(validation(settings, play_row, play_col, keep_play));

  for(i = 0; i <= play_row; i++)
    for(j = 0; j <= play_col; j++)
      settings->board[i][j] = ' ';

  if(settings->new_rule_p2 == 1) {
    printf("%s's play -> Increased game board size %c %d\n\n",
            settings->player2, play_col + 'A', play_row + 1);
    settings->new_rule_p2 = 2;
  } else
    printf("%s's play -> %c %d\n\n",
            settings->player2, play_col + 'A', play_row + 1);

  print_board(*settings);
}

void game_bot()
{
    Board settings;
    play_t *head = NULL;
    int keep_play = 1, option;

    set_rules_bot(&settings);
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

          play_bot(&settings, &keep_play);
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
          save_game_bot(&settings, head);
          keep_play = 0;
          break;

        default:
          printf("Invalid Option!\nPress any key to continue.");
          getchar();
          break;
      }

    } while(keep_play);

    if(option == 1) {
      printf("%s, you won!\n", settings.curr_player);
      save_file(head);
    }
    free_game_mem(&settings, &head);
}

void restart_game_bot()
{
    Board settings;
    play_t *head = NULL;
    int keep_play = 1, option;

    load_game_bot(&settings, &head);

    do {
      print_board(settings);
      menu_game(settings, &option);

      switch(option)
      {
        case 1:
          play(&settings, &keep_play);
          add_play(&settings, &head);
          change_player(&settings);

          play_bot(&settings, &keep_play);
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
          save_game_bot(&settings, head);
          keep_play = 0;
          break;

        default:
          printf("Invalid Option!\nPress any key to continue.");
          getchar();
          break;
      }

    } while(keep_play);

    if(option == 1) {
      printf("%s, you won!\n", settings.curr_player);
      save_file(head);
    }
    free_game_mem(&settings, &head);
}

void menu_gametype()
{
  int option;

  printf("1. Human vs Human\n2. Human vs BOT\nOption: ");
  do {
    scanf("%d", &option);
    getchar();
  }while(option != 1 && option != 2);

  switch(option) {
    case 1:
      game_players();
      break;
    case 2:
      game_bot();
      break;
  }
}

void menu_restart_game()
{
  int option;

  printf("1. Human vs Human\n2. Human vs BOT\nOption: ");
  do {
    scanf("%d", &option);
    getchar();
  }while(option != 1 && option != 2);

  switch(option) {
    case 1:
      restart_game_players();
      break;
    case 2:
      restart_game_bot();
      break;
  }
}

void menu()
{
  int option;
  char confirmation;

  do {
    printf("\t1. New Game\n\t2. Load Last Game\n\t3. Credits\n\t4. How to Play"
           "\n\t5. Quit Game\nOption: ");
    scanf("%d", &option);
    getchar();

    switch(option) {
      case 1:
        menu_gametype();
        break;

      case 2:
        printf("Load last game\n");
        menu_restart_game();
        break;

      case 3:
        printf("Author: Guilherme José Rodrigues Garrucho 21230252"
               "\nPress any key to continue. ");
        getchar();
        break;

      case 4:
        printf("\nJogo do Comilao is played with two players or against a bot,\n"
               "with a board divided by cells, identified by its size, rows \n"
               "and columns. The columns are represented by letters and the \n"
               "lines with numbers. All the cells contain food, represented \n"
               "by *, except the bottom cell of the right side of the board,\n"
               "which cotains the venom. The objetive of the game is to     \n"
               "force your opponent to eat the venom.\n\n"
               "When you start a game, every player has to enter his/her name.\n"
               "The first player chooses the size of the game board and the \n"
               "second, if he/she agrees, accepts it and the game starts.\n\n"
               "When the game begins, it will present you a menu:\n"
               "\tYou can choose to play, which you means you insert the \n"
               "\tcoordinates and the game board is clear vertically and \n"
               "\thorizontally until the cell selected, never exceeding \n"
               "\tthe limits of the line and column of the selected cell.\n\n"
               "\tYou can increase the game board size by one line and one \n"
               "\tcolumn, simultaneously, but only once during a game.\n\n"
               "\tYou can check every play of all the players, during the\n"
               "\tgame.\n\n"
               "\tAnd lastly, you can interrupt the game, save it, so you can\n"
               "\tcontinue, whenever you want you.\n\n");
        printf("\nPress any key to continue\n");
        getchar();
        break;

      case 5:
        printf("Are you sure? (Y/N)");
        scanf("%c", &confirmation);
        break;

      default:
        printf("Invalid option!\nPress any key to continue!");
        getchar();
        printf("\n\n");
        break;
    }
  } while((confirmation != 'Y' && confirmation != 'y') || option != 5);
}

int main(void)
{
  menu();
  return 0;
}
