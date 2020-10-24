/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 12:43:43 by gicho             #+#    #+#             */
/*   Updated: 2020/10/24 12:43:43 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

void	calc_draw_info(t_draw_info *info, t_cub *cub, int x)
{
	int h;

	h = cub->window.height;
	info->ray = init_ray(cub->player, x, cub->window.width);
	info->perp_wall_dist = calc_perp_wall_dist(cub, &(info->ray));
	info->line_h = (int)(h / info->perp_wall_dist);
	info->draw_s = info->line_h > h ? 0 : (h - info->line_h) / 2;
	info->draw_e = info->line_h >= h ? h - 1 : (info->line_h + h) / 2;
	if (info->ray.side)
	{
		info->tex_n = info->ray.dir.y > 0 ? 0 : 1;
		info->wall_x = cub->player.pos.x + info->perp_wall_dist
		* info->ray.dir.x;
	}
	else
	{
		info->tex_n = info->ray.dir.x > 0 ? 2 : 3;
		info->wall_x = cub->player.pos.y + info->perp_wall_dist
		* info->ray.dir.y;
	}
	info->wall_x -= floor(info->wall_x);
	cub->zbuf[x] = info->perp_wall_dist;
}

void	calc_draw_tex_info(t_draw_tex_info *tex_info,
							t_cub *cub, t_draw_info *info)
{
	tex_info->tex_w = cub->texture[info->tex_n].size.x;
	tex_info->tex_h = cub->texture[info->tex_n].size.y;
	tex_info->tex_x = (int)(info->wall_x * (double)tex_info->tex_w);
	if ((info->ray.side == 0 && info->ray.dir.x > 0) ||
		(info->ray.side == 1 && info->ray.dir.y < 0))
		tex_info->tex_x = tex_info->tex_w - tex_info->tex_x - 1;
	tex_info->step = 1.0 * tex_info->tex_h / info->line_h;
	tex_info->tex_pos = (info->draw_s - cub->window.height / 2
							+ info->line_h / 2) * tex_info->step;
}

int		get_tex_color(t_draw_tex_info *tex_info, t_cub *cub, t_draw_info *info)
{
	int tex_y;
	int pos;

	tex_y = (int)tex_info->tex_pos & (tex_info->tex_h - 1);
	pos = tex_info->tex_h * tex_y + tex_info->tex_x;
	return (cub->texture[info->tex_n].data[pos]);
}

void	draw_wall(t_cub *cub)
{
	int				x;
	int				y;
	t_draw_info		info;
	t_draw_tex_info	tex_info;

	x = -1;
	while (++x < cub->window.width)
	{
		calc_draw_info(&info, cub, x);
		calc_draw_tex_info(&tex_info, cub, &info);
		y = info.draw_s - 1;
		while (++y < info.draw_e)
		{
			cub->window.scene[y][x] = get_tex_color(&tex_info, cub, &info);
			tex_info.tex_pos += tex_info.step;
		}
	}
}
