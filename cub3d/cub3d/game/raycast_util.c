/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 12:43:43 by gicho             #+#    #+#             */
/*   Updated: 2020/10/24 12:43:43 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

t_pair_double	calc_side_dist(t_ray ray, t_pair_double delta_dist,
								double pos_x, double pos_y)
{
	t_pair_double side_dist;

	if (ray.dir.x < 0)
		side_dist.x = (pos_x - ray.map.x) * delta_dist.x;
	else
		side_dist.x = (ray.map.x + 1.0 - pos_x) * delta_dist.x;
	if (ray.dir.y < 0)
		side_dist.y = (pos_y - ray.map.y) * delta_dist.y;
	else
		side_dist.y = (ray.map.y + 1.0 - pos_y) * delta_dist.y;
	return (side_dist);
}

t_pair_int		calc_step(t_ray ray)
{
	t_pair_int step;

	if (ray.dir.x < 0)
		step.x = -1;
	else
		step.x = 1;
	if (ray.dir.y < 0)
		step.y = -1;
	else
		step.y = 1;
	return (step);
}

t_pair_double	calc_delta_dist(t_ray ray)
{
	t_pair_double delta_dist;

	delta_dist.x = fabs(1 / ray.dir.x);
	delta_dist.y = fabs(1 / ray.dir.y);
	return (delta_dist);
}
