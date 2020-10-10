#ifndef PLAYER_H
# define PLAYER_H

#include <math.h>
#include "type.h"

t_player	initPlayer(void);
void		update_player(int **map, t_player *player);

#endif
