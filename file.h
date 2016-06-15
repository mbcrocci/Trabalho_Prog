#ifndef file_h_
#define file_h_

#include "main.h"

void save_game(Board * settings, play_t * head);
void save_game_bot(Board * settings, play_t * head);
void save_file(play_t * head);
void load_settings(FILE * old_settings, Board * settings, play_t ** head );
void load_game(Board * settings, play_t **head);
void load_game_bot(Board * settings, play_t **head);

#endif
