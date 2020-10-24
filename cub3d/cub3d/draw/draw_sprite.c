/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 12:43:43 by gicho             #+#    #+#             */
/*   Updated: 2020/10/24 12:43:43 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

int		compare(t_sprite *lhs, t_sprite *rhs)
{
	int lhs_dist;
	int rhs_dist;

	lhs_dist = pow(lhs->pos.x - g_cub.player.pos.x, 2)
				+ pow(lhs->pos.y - g_cub.player.pos.y, 2);
	rhs_dist = pow(rhs->pos.x - g_cub.player.pos.x, 2)
				+ pow(rhs->pos.y - g_cub.player.pos.y, 2);
	return (lhs_dist < rhs_dist);
}

void	calc_draw_sprite_info(t_draw_sprite_info *info, t_sprite *sprite)
{
	info->w = g_cub.window.width;
	info->h = g_cub.window.height;
	info->sprite_x = sprite->pos.x - g_cub.player.pos.x;
	info->sprite_y = sprite->pos.y - g_cub.player.pos.y;
	info->inv_det = 1.0 / (g_cub.player.plane.x * g_cub.player.dir.y -
							g_cub.player.dir.x * g_cub.player.plane.y);
	info->transform_x = info->inv_det * (g_cub.player.dir.y * info->sprite_x
									- g_cub.player.dir.x * info->sprite_y);
	info->transform_y = info->inv_det * (-g_cub.player.plane.y * info->sprite_x
									+ g_cub.player.plane.x * info->sprite_y);
	info->sprite_screen_x = (int)((info->w / 2)
								* (1 + info->transform_x / info->transform_y));
	info->sprite_h = abs((int)(info->h / (info->transform_y)));
	info->draw_start_y = ft_max(0, -info->sprite_h / 2 + info->h / 2);
	info->draw_end_y = ft_min(info->h - 1, info->sprite_h / 2 + info->h / 2);
	info->sprite_w = abs((int)(info->h / (info->transform_y)));
	info->draw_start_x = ft_max(0, -info->sprite_w / 2 + info->sprite_screen_x);
	info->draw_end_x = ft_min(info->w - 1,
							info->sprite_w / 2 + info->sprite_screen_x);
	info->tex_width = g_cub.texture[4].size.x;
	info->tex_height = g_cub.texture[4].size.y;
}

void	draw_ele_sub(t_draw_sprite_info *info, t_sprite *sprite, int stripe)
{
	int y;
	int tmp;

	y = info->draw_start_y - 1;
	while (++y < info->draw_end_y)
	{
		info->d = (y) * 256 - info->h * 128 + info->sprite_h * 128;
		info->tex_y = (info->d * info->tex_height) / info->sprite_h / 256;
		tmp = info->tex_width * info->tex_y + info->tex_x;
		info->color = g_cub.texture[sprite->tex_num].data[tmp];
		if ((info->color & 0x00FFFFFF) != 0)
			g_cub.window.scene[y][stripe] = info->color;
	}
}

void	draw_ele(t_sprite *sprite)
{
	t_draw_sprite_info	info;
	int					stripe;
	int					tmp;

	calc_draw_sprite_info(&info, sprite);
	stripe = info.draw_start_x - 1;
	while (++stripe < info.draw_end_x)
	{
		tmp = stripe - (-info.sprite_w / 2 + info.sprite_screen_x);
		info.tex_x = (int)(256 * tmp * info.tex_width / info.sprite_w) / 256;
		if (stripe > 0 && stripe < info.w && info.transform_y > 0
			&& info.transform_y < g_cub.zbuf[stripe])
			draw_ele_sub(&info, sprite, stripe);
	}
}

void	draw_sprite(t_cub *cub)
{
	ft_list_sort(&cub->sprite, compare);
	ft_list_foreach(cub->sprite, draw_ele);
}
