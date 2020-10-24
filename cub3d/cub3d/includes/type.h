/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 12:43:43 by gicho             #+#    #+#             */
/*   Updated: 2020/10/24 12:43:43 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_H
# define TYPE_H

# include "libft.h"

enum			e_key {
	key_arrow_up = 126,
	key_arrow_down = 125,
	key_arrow_left = 123,
	key_arrow_right = 124,
	key_w = 13,
	key_a = 0,
	key_s = 1,
	key_d = 2
};

typedef struct	s_window {
	int width;
	int height;
	int **scene;
}				t_window;

typedef struct	s_pair_int {
	int x;
	int y;
}				t_pair_int;

typedef struct	s_pair_double {
	double x;
	double y;
}				t_pair_double;

typedef struct	s_control {
	int			keyboard[101];
	t_pair_int	old_mouse_point;
	t_pair_int	new_mouse_point;
}				t_control;

typedef struct	s_point_of_view
{
	int horizontal;
	int vertical;
}				t_point_of_view;

typedef struct	s_player
{
	t_pair_double	pos;
	t_pair_double	dir;
	t_pair_double	plane;
	t_point_of_view	movement;
	t_point_of_view	rotation;

}				t_player;

typedef struct	s_ray{
	t_pair_int		map;
	t_pair_double	dir;
	int				side;
}				t_ray;

typedef struct	s_rgb{
	int r;
	int g;
	int b;
}				t_rgb;

typedef struct	s_map {
	t_pair_int	size;
	char		**data;
}				t_map;

typedef struct	s_texture {
	t_pair_int	size;
	int			*data;
}				t_texture;

typedef struct	s_sprite {
	t_pair_double	pos;
	int				tex_num;
}				t_sprite;

typedef struct	s_cub {
	t_window	window;
	t_player	player;
	t_texture	texture[5];
	t_rgb		floor;
	t_rgb		ceil;
	t_list		*sprite;
	t_map		map;
	t_control	control;
	double		*zbuf;
}				t_cub;

typedef struct	s_string_array {
	int		size;
	char	**ele;
}				t_string_array;

enum			e_conf_flags {
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

typedef struct	s_mlx {
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	int		*data;
	int		bpp;
	int		sl;
	int		endian;
}				t_mlx;

typedef struct	s_draw_info{
	t_ray	ray;
	double	perp_wall_dist;
	int		line_h;
	int		draw_s;
	int		draw_e;
	int		tex_n;
	double	wall_x;
}				t_draw_info;

typedef struct	s_draw_tex_info{
	int		tex_w;
	int		tex_h;
	int		tex_x;
	double	step;
	double	tex_pos;
}				t_draw_tex_info;

typedef struct	s_draw_sprite_info{
	int				w;
	int				h;
	double			sprite_x;
	double			sprite_y;
	double			inv_det;
	double			transform_x;
	double			transform_y;
	int				sprite_screen_x;
	int				sprite_h;
	int				draw_start_y;
	int				draw_end_y;
	int				sprite_w;
	int				draw_start_x;
	int				draw_end_x;
	int				tex_width;
	int				tex_height;
	int				tex_x;
	int				tex_y;
	int				d;
	unsigned int	color;
}				t_draw_sprite_info;

#endif
