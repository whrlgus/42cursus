/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 12:43:43 by gicho             #+#    #+#             */
/*   Updated: 2020/10/24 12:43:43 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

void	dda(t_ray *ray, char **map, t_pair_double side_dist)
{
	t_pair_double	delta_dist;
	t_pair_int		step;

	delta_dist = calc_delta_dist(*ray);
	step = calc_step(*ray);
	while (1)
	{
		if (side_dist.x < side_dist.y)
		{
			side_dist.x += delta_dist.x;
			ray->map.x += step.x;
			ray->side = 0;
		}
		else
		{
			side_dist.y += delta_dist.y;
			ray->map.y += step.y;
			ray->side = 1;
		}
		if (map[ray->map.x][ray->map.y] == '1')
			break ;
	}
}

double	calc_perp_wall_dist(t_cub *cub, t_ray *ray)
{
	t_pair_double	delta_dist;
	t_pair_double	side_dist;
	t_pair_int		step;

	delta_dist = calc_delta_dist(*ray);
	side_dist = calc_side_dist(*ray, delta_dist,
								cub->player.pos.x, cub->player.pos.y);
	step = calc_step(*ray);
	dda(ray, cub->map.data, side_dist);
	if (ray->side == 0)
		return ((ray->map.x - cub->player.pos.x + (1 - step.x) / 2)
				/ ray->dir.x);
	else
		return ((ray->map.y - cub->player.pos.y + (1 - step.y) / 2)
				/ ray->dir.y);
}

t_ray	init_ray(t_player player, int x, int w)
{
	t_ray	ray;
	double	camera_x;

	camera_x = 2 * x / (double)w - 1;
	ray.dir.x = player.dir.x + player.plane.x * camera_x;
	ray.dir.y = player.dir.y + player.plane.y * camera_x;
	ray.map.x = (int)player.pos.x;
	ray.map.y = (int)player.pos.y;
	return (ray);
}
