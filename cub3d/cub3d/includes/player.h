#ifndef PLAYER_H
# define PLAYER_H

#include <math.h>
#include "utility.h"


void		update_player(char **map, t_player *player);
t_player init_player(t_map *map);
t_pair_double	calc_dir(t_player *p);
void update_position_sub(char **map, t_player *p, t_pair_double dir);
#endif
