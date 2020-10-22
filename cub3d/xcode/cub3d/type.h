#ifndef type_h
#define type_h

#include "libft.h"

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

typedef struct s_window {
	int width;
	int height;
	int **scene;
}t_window;

typedef struct s_pair_int {
	int x,y;
}				t_pair_int;

typedef struct s_pair_double {
	double x,y;
}				t_pair_double;

typedef struct s_control {
	int keyboard[101];
	t_pair_int old_mouse_point, new_mouse_point;
}				t_control;

typedef struct	s_point_of_view
{
	int horizontal, vertical;
}				t_point_of_view;

typedef struct	s_player
{
	t_pair_double pos;
	t_pair_double dir;
	t_pair_double plane;
	t_point_of_view movement;
	t_point_of_view rotation;

}				t_player;

typedef struct s_ray{
	t_pair_int map;
	t_pair_double dir;
	int side;
}t_ray;

typedef struct s_rgb{
	int r;
	int g;
	int b;
}t_rgb;

typedef struct s_map {
	t_pair_int size;
	char **data;
}t_map;

typedef struct s_texture {
	t_pair_int size;
	int *data;
}t_texture;

typedef struct s_sprite {
	t_pair_double pos;
	int tex_num;
}t_sprite;

typedef struct s_cub {
	t_window window;
	t_player player;
	t_texture texture[5];
	t_rgb floor;
	t_rgb ceil;
	t_list *sprite;
	t_map map;
	t_control control;
	double *zbuf;
}t_cub;

typedef struct s_string_array {
	int size;
	char **ele;
}t_string_array;

enum e_conf_flags {
	resolution_f,
	north_f,
	south_f,
	west_f,
	east_f,
	sprite_f,
	floor_f,
	ceil_f,
	map_f
};



#endif /* type_h */
