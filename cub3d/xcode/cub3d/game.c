#include "game.h"

t_player g_player;
t_window g_window;
int **g_map;
t_control g_control;

void init_game() {
	g_map = initMap();
	g_player = initPlayer();
	g_window = init_window(640, 480);
}


