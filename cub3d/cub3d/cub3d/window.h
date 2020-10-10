#ifndef window_h
#define window_h

#include "type.h"
#include "texture.h"
#include <stdlib.h>
#include "raycast.h"
extern int **texture;

t_window init_window(int width, int height);
void update_scene(int **map, t_window g_window, t_player player);

#endif /* window_h */
