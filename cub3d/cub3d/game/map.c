/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 12:43:43 by gicho             #+#    #+#             */
/*   Updated: 2020/10/24 12:43:43 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

char		**init_map(char **strs, int start, t_pair_int size)
{
	char	**map;
	int		i;
	int		j;

	map = init_chars_array(size.y, size.x, ' ');
	i = 0;
	j = 0;
	while (i < size.y)
	{
		j = (int)ft_strlen(strs[start + i]);
		while (--j >= 0)
			map[i][j] = strs[start + i][j];
		++i;
	}
	return (map);
}

t_pair_int	calc_size(t_string_array *arr, int i)
{
	t_pair_int	ret;
	int			len;

	ft_memset(&ret, 0, sizeof(ret));
	while (i < arr->size &&
			(len = (int)ft_strlen(arr->ele[i])) &&
			is_included(arr->ele[i][0], " 01"))
	{
		++ret.y;
		ret.x = ft_max(ret.x, len);
		++i;
	}
	return (ret);
}
