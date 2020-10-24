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
	info->spriteX = sprite->pos.x - g_cub.player.pos.x;
	info->spriteY = sprite->pos.y - g_cub.player.pos.y;
	info->invDet = 1.0 / (g_cub.player.plane.x * g_cub.player.dir.y -
							g_cub.player.dir.x * g_cub.player.plane.y);
	info->transformX = info->invDet * (g_cub.player.dir.y * info->spriteX
									- g_cub.player.dir.x * info->spriteY);
	info->transformY = info->invDet * (-g_cub.player.plane.y * info->spriteX
									+ g_cub.player.plane.x * info->spriteY);
	info->spriteScreenX = (int)((info->w / 2)
								* (1 + info->transformX / info->transformY));
	info->spriteHeight = abs((int)(info->h / (info->transformY)));
	info->drawStartY = ft_max(0, -info->spriteHeight / 2 + info->h / 2);
	info->drawEndY = ft_min(info->h - 1, info->spriteHeight / 2 + info->h / 2);
	info->spriteWidth = abs((int)(info->h / (info->transformY)));
	info->drawStartX = ft_max(0, -info->spriteWidth / 2 + info->spriteScreenX);
	info->drawEndX = ft_min(info->w - 1,
							info->spriteWidth / 2 + info->spriteScreenX);
	info->texWidth = g_cub.texture[4].size.x;
	info->texHeight = g_cub.texture[4].size.y;
}

void	draw_ele_sub(t_draw_sprite_info *info, t_sprite *sprite, int stripe)
{
	int y;
	int tmp;

	y = info->drawStartY - 1;
	while (++y < info->drawEndY)
	{
		info->d = (y) * 256 - info->h * 128 + info->spriteHeight * 128;
		info->texY = (info->d * info->texHeight) / info->spriteHeight / 256;
		tmp = info->texWidth * info->texY + info->texX;
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
	stripe = info.drawStartX - 1;
	while (++stripe < info.drawEndX)
	{
		tmp = stripe - (-info.spriteWidth / 2 + info.spriteScreenX);
		info.texX = (int)(256 * tmp * info.texWidth / info.spriteWidth) / 256;
		if (stripe > 0 && stripe < info.w && info.transformY > 0
			&& info.transformY < g_cub.zbuf[stripe])
			draw_ele_sub(&info, sprite, stripe);
	}
}

void	draw_sprite(t_cub *cub)
{
	ft_list_sort(&cub->sprite, compare);
	ft_list_foreach(cub->sprite, draw_ele);
}
