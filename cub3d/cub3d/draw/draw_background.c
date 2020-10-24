/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 12:43:43 by gicho             #+#    #+#             */
/*   Updated: 2020/10/24 12:43:43 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

void	draw_background(t_window *window, t_rgb floor, t_rgb ceil)
{
	int i;
	int j;

	i = -1;
	while (++i < window->width)
	{
		j = -1;
		while (++j < window->height / 2)
			window->scene[j][i] = (ceil.r << 16) + (ceil.g << 8) + ceil.b;
		while (j < window->height)
			window->scene[j++][i] = (floor.r << 16) + (floor.g << 8) + floor.b;
	}
}
