#ifndef PLAYER_H
# define PLAYER_H

#include <math.h>

typedef struct s_pair_double {
	double x,y;
}				t_pair_double;

typedef struct	s_player
{
	t_pair_double pos;
	t_pair_double dir;
	t_pair_double plane;

}				t_player;

typedef struct	s_point_of_view
{
	int horizontal, vertical;
}				t_point_of_view;

void			update_player(int **worldMap,
							  t_player *player,
							  t_point_of_view *movement,
							  t_point_of_view *rotation);
#endif
