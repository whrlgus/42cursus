/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 12:43:43 by gicho             #+#    #+#             */
/*   Updated: 2020/10/24 12:43:43 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

t_window	init_window(int width, int height)
{
	t_window	window;
	int			i;

	width = ft_min(1000, width);
	width = ft_max(100, width);
	if (width * 3 != height * 4)
		height = (double)width * 3 / 4;
	window.width = width;
	window.height = height;
	window.scene = (int**)malloc(window.height * sizeof(int*));
	i = -1;
	while (++i < window.height)
		window.scene[i] = (int*)malloc(window.width * sizeof(int));
	return (window);
}

void		update_scene(void)
{
	draw_background(&g_cub.window, g_cub.floor, g_cub.ceil);
	draw_wall(&g_cub);
	draw_sprite(&g_cub);
}
