#ifndef game_h
#define game_h

#include "player.h"
#include "map.h"
#include "window.h"
#include "texture.h"
#include "control.h"
extern t_cub g_cub;
extern t_player g_player;
extern int **g_map;
extern t_window g_window;
extern t_control g_control;

void init_game(void);

#endif
