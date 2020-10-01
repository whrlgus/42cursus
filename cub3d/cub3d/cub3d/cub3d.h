#ifndef CUB3D_H
# define CUB3D_H

#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480

# include "mlx.h"
# include "player.h"

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


typedef enum e_direction {
	right=0,left,forward,backward
}	t_direction;



typedef struct s_pair_int {
	int x,y;
}				t_pair_int;

extern void *mlx_ptr;
extern void *win_ptr;
extern int **worldMap;
extern int map[mapWidth][mapHeight];
//extern double posX, posY;  //x and y start position
//extern double dirX, dirY; //initial direction vector
//extern double planeX, planeY;
extern int stop;

extern void *img_ptr;
extern int *data;

extern int bpp;
extern int sl;
extern int endian;

void redraw(t_player *player);
void move_position(void);

#endif
