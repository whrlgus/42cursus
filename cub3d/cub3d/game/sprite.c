/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 12:43:43 by gicho             #+#    #+#             */
/*   Updated: 2020/10/24 12:43:43 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sprite.h"

int	init_sprite(t_list **head, t_map *map)
{
	int			i;
	int			j;
	t_sprite	*sprite;

	i = -1;
	while (++i < map->size.y)
	{
		j = -1;
		while (++j < map->size.x)
			if (is_included(map->data[i][j], "2"))
			{
				sprite = malloc(sizeof(t_sprite));
				sprite->pos.x = 0.5 + i;
				sprite->pos.y = 0.5 + j;
				sprite->tex_num = 4;
				ft_list_push_back(head, (void*)sprite);
			}
	}
	return (1);
}
