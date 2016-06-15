#ifndef board_h_
#define board_h_

#include "main.h"

void create_board(Board * settings);
void free_game_mem(Board *settings, play_t ** head);
void print_board(Board settings);
int get_pos(Board * settings, int play_row, int play_col);
void validation_new_rule(Board * settings);
void new_rule(Board * settings);

#endif
