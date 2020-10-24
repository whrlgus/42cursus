/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 12:43:43 by gicho             #+#    #+#             */
/*   Updated: 2020/10/24 12:43:43 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"

int	load_texture(t_texture *texture, char *file_path)
{
	int		tmp;
	void	*img;

	img = mlx_xpm_file_to_image(g_mlx.mlx_ptr,
								file_path,
								&texture->size.x,
								&texture->size.y);
	if (!img)
		return (0);
	texture->data = (int *)mlx_get_data_addr(img, &tmp, &tmp, &tmp);
	return (texture->data != 0);
}
