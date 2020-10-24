/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 12:43:43 by gicho             #+#    #+#             */
/*   Updated: 2020/10/24 12:43:43 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

void		update_position(char **map, t_player *p, t_pair_double dir)
{
	double			move_speed;
	double			n_pos_x;
	double			n_pos_y;
	t_pair_double	ndir;

	move_speed = 0.05;
	n_pos_x = p->pos.x + dir.x * move_speed;
	n_pos_y = p->pos.y + dir.y * move_speed;
	ndir.x = n_pos_x;
	ndir.y = p->pos.y;
	update_position_sub(map, p, ndir);
	ndir.x = p->pos.x;
	ndir.y = n_pos_y;
	update_position_sub(map, p, ndir);
}

void		update_direction(t_player *p)
{
	double rot_speed;
	double old_dir_x;
	double old_plane_x;

	rot_speed = 0.02 * p->rotation.horizontal;
	old_dir_x = p->dir.x;
	p->dir.x = p->dir.x * cos(rot_speed) - p->dir.y * sin(rot_speed);
	p->dir.y = old_dir_x * sin(rot_speed) + p->dir.y * cos(rot_speed);
	old_plane_x = p->plane.x;
	p->plane.x = p->plane.x * cos(rot_speed) - p->plane.y * sin(rot_speed);
	p->plane.y = old_plane_x * sin(rot_speed) + p->plane.y * cos(rot_speed);
}

void		update_player(char **map, t_player *p)
{
	t_pair_double old_dir;
	t_pair_double old_plane;

	old_dir.x = p->dir.x;
	old_dir.y = p->dir.y;
	old_plane.x = p->plane.x;
	old_plane.y = p->plane.y;
	if (p->movement.horizontal || p->movement.vertical)
		update_position(map, p, calc_dir(p));
	if (p->rotation.horizontal || p->rotation.vertical)
		update_direction(p);
}

void		set_player(t_player *p, int x, int y, char dir)
{
	p->pos.x = 0.5 + y;
	p->pos.y = 0.5 + x;
	if (dir == 'E')
	{
		p->dir.y = 1;
		p->plane.x = 0.66;
	}
	else if (dir == 'W')
	{
		p->dir.y = -1;
		p->plane.x = -0.66;
	}
	else if (dir == 'S')
	{
		p->dir.x = 1;
		p->plane.y = -0.66;
	}
	else
	{
		p->dir.x = -1;
		p->plane.y = 0.66;
	}
}

t_player	init_player(t_map *map)
{
	t_player	p;
	int			i;
	int			j;

	ft_bzero(&p, sizeof(p));
	i = -1;
	while (++i < map->size.y)
	{
		j = -1;
		while (++j < map->size.x)
			if (is_included(map->data[i][j], "EWSN"))
			{
				set_player(&p, j, i, map->data[i][j]);
				map->data[i][j] = '0';
				return (p);
			}
	}
	return (p);
}
