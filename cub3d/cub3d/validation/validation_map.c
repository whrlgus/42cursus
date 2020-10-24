/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 12:43:43 by gicho             #+#    #+#             */
/*   Updated: 2020/10/24 12:43:43 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"

static int	visit(char ***map, int i, int j, t_pair_int size)
{
	int			d;
	t_pair_int	next;

	if (i == 0 || j == 0 || i == size.y - 1
		|| j == size.x - 1 || (*map)[i][j] == ' ')
		return (0);
	(*map)[i][j] = '1';
	d = 0;
	while (d < 4)
	{
		next = next_pos(i, j, d);
		if ((*map)[next.y][next.x] != '1'
			&& !visit(map, next.y, next.x, size))
			return (0);
		++d;
	}
	return (1);
}

static int	check_bound(char **map, t_pair_int size)
{
	int r;
	int c;

	r = 1;
	while (r < size.y)
	{
		c = 1;
		while (c < size.x)
		{
			if (map[r][c] != ' ' &&
				map[r][c] != '1' &&
				!visit(&map, r, c, size))
				return (0);
			++c;
		}
		++r;
	}
	return (1);
}

static int	is_include_valid_char(char **map, t_pair_int size)
{
	int		i;
	int		j;
	char	dir;

	dir = 0;
	i = -1;
	while (++i < size.y)
	{
		j = -1;
		while (++j < size.x)
		{
			if (is_included(map[i][j], " 012"))
				continue;
			if (!is_included(map[i][j], "EWSN") || dir)
				return (0);
			dir = map[i][j];
		}
	}
	return (dir);
}

int			is_valid_map(t_string_array *conf, int *i, int chk[])
{
	int			ret;
	t_pair_int	size;
	char		**map;

	if (chk[map_f])
		return (0);
	chk[map_f] = 1;
	ret = 1;
	size = calc_size(conf, *i);
	if (size.x < 3 || size.y < 3)
		ret = 0;
	else
	{
		map = init_map(conf->ele, *i, size);
		if (!is_include_valid_char(map, size) || !check_bound(map, size))
			ret = 0;
		free_2d_arr(map, size.y);
	}
	*i += (size.y - 1);
	return (ret);
}
