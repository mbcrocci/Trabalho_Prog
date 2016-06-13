#ifndef play_h_
#define play_h_

#include "main.h"

void play_history(play_t * head);
void board_copy(Board * settings, play_t * new_play);
void add_play(Board * settings, play_t ** head);
#endif
