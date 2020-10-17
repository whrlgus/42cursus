#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include "game.h"

#include <unistd.h>
#include <string.h>

typedef struct s_mlx {
	void *mlx_ptr;
	void *win_ptr;
	void *img_ptr;
	int *data;
	int bpp;
	int sl;
	int endian;
}t_mlx;

#endif
