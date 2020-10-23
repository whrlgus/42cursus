#ifndef draw_h
#define draw_h

#include "type.h"
#include "raycast.h"
#include "game.h"
#include "utility.h"

void draw_sprite(t_cub *cub);
void draw_wall(t_cub *cub);
void draw_background(t_window *window, t_rgb floor, t_rgb ceil);

#endif 
