#ifndef main_h_
#define main_h_

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

#endif
