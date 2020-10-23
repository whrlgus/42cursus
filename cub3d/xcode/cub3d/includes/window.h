#ifndef window_h
#define window_h

#include "type.h"
#include "texture.h"
#include <stdlib.h>
#include "draw.h"

t_window init_window(int width, int height);
void update_scene(char **map, t_window g_window, t_player player);

#endif /* window_h */
