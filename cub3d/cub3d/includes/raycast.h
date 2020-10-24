/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 12:43:43 by gicho             #+#    #+#             */
/*   Updated: 2020/10/24 12:43:43 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include "type.h"
# include <math.h>

t_pair_double	calc_side_dist(t_ray ray, t_pair_double delta_dist,
								double pos_x, double pos_y);
t_pair_int		calc_step(t_ray ray);
t_pair_double	calc_delta_dist(t_ray ray);
double			calc_perp_wall_dist(t_cub *cub, t_ray *ray);
t_ray			init_ray(t_player player, int x, int w);

#endif
