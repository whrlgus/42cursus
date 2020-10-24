/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 12:43:43 by gicho             #+#    #+#             */
/*   Updated: 2020/10/24 12:43:43 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

t_pair_double	calc_dir(t_player *p)
{
	t_pair_double dir;

	dir.x = p->dir.x;
	dir.y = p->dir.y;
	if (p->movement.horizontal && p->movement.vertical)
	{
		dir.x = (p->movement.vertical * p->dir.x
				+ p->movement.horizontal * p->dir.y) / sqrt(2);
		dir.y = (p->movement.vertical * p->dir.y
				- p->movement.horizontal * p->dir.x) / sqrt(2);
	}
	else if (p->movement.horizontal)
	{
		dir.x = p->movement.horizontal * p->dir.y;
		dir.y = -p->movement.horizontal * p->dir.x;
	}
	else if (p->movement.vertical)
	{
		dir.x *= p->movement.vertical;
		dir.y *= p->movement.vertical;
	}
	return (dir);
}

void			update_position_sub(char **map, t_player *p, t_pair_double dir)
{
	double	rad;
	int		i;
	int		x;
	int		y;

	rad = 0.1;
	i = -1;
	while (++i < 360)
	{
		x = dir.x + rad * cos((double)i * M_PI / 180);
		y = dir.y + rad * sin((double)i * M_PI / 180);
		if (map[x][y] != '0')
			return ;
	}
	if (map[(int)dir.x][(int)dir.y] == '0')
	{
		p->pos.y = dir.y;
		p->pos.x = dir.x;
	}
}
