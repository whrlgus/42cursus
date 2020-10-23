#ifndef game_h
#define game_h

#include "player.h"
#include "map.h"
#include "window.h"
#include "texture.h"
#include "control.h"
#include "error.h"
#include "fileio.h"
#include "validation.h"
#include "sprite.h"

extern t_cub g_cub;

int init_game(char *cub_file_path);
int set_cub(t_cub *cub, t_string_array *conf);
#endif
