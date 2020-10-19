#ifndef PLAYER_H
# define PLAYER_H

#include <math.h>
#include "utility.h"

t_player	initPlayer(void);
void		update_player(char **map, t_player *player);
t_player init_player(t_map *map);
#endif
