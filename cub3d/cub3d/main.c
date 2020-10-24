/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 17:12:46 by gicho             #+#    #+#             */
/*   Updated: 2020/10/24 17:12:46 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_mlx g_mlx;

void	redraw(t_mlx mlx)
{
	int i;
	int j;
	int tmp;

	i = -1;
	while (++i < g_cub.window.height)
	{
		j = -1;
		tmp = i * mlx.sl / 4;
		while (++j < g_cub.window.width)
			mlx.data[tmp + j] = g_cub.window.scene[i][j];
	}
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, mlx.img_ptr, 0, 0);
}

int		loop(t_mlx *mlx)
{
	calc_movement(&g_cub.player, &g_cub.control);
	update_player(g_cub.map.data, &g_cub.player);
	update_scene();
	redraw(*mlx);
	return (0);
}

void	init_mlx(void)
{
	g_mlx.win_ptr = mlx_new_window(g_mlx.mlx_ptr, g_cub.window.width,
								g_cub.window.height, "gicho");
	g_mlx.img_ptr = mlx_new_image(g_mlx.mlx_ptr, g_cub.window.width,
								g_cub.window.height);
	g_mlx.data = (int *)mlx_get_data_addr(g_mlx.img_ptr, &g_mlx.bpp,
										&g_mlx.sl, &g_mlx.endian);
	mlx_hook(g_mlx.win_ptr, 2, 0, key_pressed, &g_cub.control);
	mlx_hook(g_mlx.win_ptr, 3, 0, key_released, &g_cub.control);
	mlx_hook(g_mlx.win_ptr, 6, 0, motion_notified, &g_cub.control);
	mlx_hook(g_mlx.win_ptr, 17, 0, exit_hook, 0);
	mlx_loop_hook(g_mlx.mlx_ptr, loop, &g_mlx);
	mlx_loop(g_mlx.mlx_ptr);
}

int		main(int argc, const char *argv[])
{
	g_mlx.mlx_ptr = mlx_init();
	if (argc > 3 || argc == 1
		|| (argc == 3 && ft_strcmp("--save", argv[2]) != 0))
		return (print_error(cuberror(invalid_argument)));
	if (!init_game((char*)argv[1]))
		return (-1);
	if (argc == 3)
	{
		update_scene();
		save_image_to_bmp_file(g_cub.window.scene, g_cub.window.width,
								g_cub.window.height);
	}
	else
		init_mlx();
	return (0);
}
