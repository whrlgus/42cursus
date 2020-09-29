#ifndef CUB3D_H
# define CUB3D_H
//#define mapWidth 24
//#define mapHeight 24
#define mapWidth 640
#define mapHeight 480
# include "mlx.h"
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>
enum Key {
	key_arrow_up = 126,
	key_arrow_down = 125,
	key_arrow_left = 123,
	key_arrow_right = 124,
	key_w = 13,
	key_a = 0,
	key_s = 1,
	key_d = 2
};
typedef struct s_player
{
	double posX,posY;
	double dirX,dirY;
	double planeX,planeY;

}				t_player;

typedef enum e_direction {
	right=0,left,forward,backward
}	t_direction;

typedef struct s_point_of_view
{
	int horizontal, vertical;
}				t_point_of_view;

typedef struct s_pair_double {
	double x,y;
}				t_pair_double;
extern void *mlx_ptr;
extern void *win_ptr;
extern int worldMap[mapWidth][mapHeight];
//extern double posX, posY;  //x and y start position
//extern double dirX, dirY; //initial direction vector
//extern double planeX, planeY;
extern int stop;

extern int move_key;
extern int rotate_key;

extern void *img_ptr;
extern int *data;

extern int bpp;
extern int sl;
extern int endian;

void redraw(t_player *player);
void move_position(void);
void	update_player(t_player *player,
					  t_point_of_view *movement,
					  t_point_of_view *rotation);

#endif
