/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_key.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 12:43:43 by gicho             #+#    #+#             */
/*   Updated: 2020/10/24 12:43:43 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"

static int	is_valid_rgb_fmt(char *str)
{
	int		ret;
	char	**token;
	int		i;
	int		cnt;

	ret = 0;
	token = ft_split(str, ',');
	if ((count_chars(str, ',') == 2) && (cnt = count_token(token)) == 3)
	{
		i = -1;
		while (++i < 3)
			if (!is_all_digit(token[i]) || ft_atoi(token[i]) > 255)
				break ;
		ret = (i == 3);
		free_2d_arr(token, cnt);
	}
	return (ret);
}

static int	is_valid_one_char_key(char **token, int cnt)
{
	if (ft_strcmp("R", token[0]) == 0)
		return (cnt == 3 && is_all_digit(token[1]) && is_all_digit(token[2]));
	if (cnt != 2)
		return (0);
	if (is_included(token[0][0], "FC") && !is_valid_rgb_fmt(token[1]))
		return (0);
	return (1);
}

static int	check(char *key, int chk[])
{
	enum e_conf_flags	flag;

	if (!ft_strcmp(key, "R"))
		flag = resolution_f;
	else if (!ft_strcmp(key, "NO"))
		flag = north_f;
	else if (!ft_strcmp(key, "SO"))
		flag = south_f;
	else if (!ft_strcmp(key, "WE"))
		flag = west_f;
	else if (!ft_strcmp(key, "EA"))
		flag = east_f;
	else if (!ft_strcmp(key, "S"))
		flag = sprite_f;
	else if (!ft_strcmp(key, "F"))
		flag = floor_f;
	else if (!ft_strcmp(key, "C"))
		flag = ceil_f;
	else
		return (0);
	if (chk[flag])
		return (0);
	return (chk[flag] = 1);
}

int			is_valid_key(char *str, int chk[])
{
	char	**token;
	int		len;
	int		cnt;
	int		ret;

	ret = 1;
	token = ft_split(str, ' ');
	if (!(cnt = count_token(token)) || !check(token[0], chk))
		ret = 0;
	else
	{
		len = (int)ft_strlen(token[0]);
		if (len == 1)
			ret = is_valid_one_char_key(token, cnt);
		else
			ret = (cnt == 2);
	}
	free_2d_arr(token, cnt);
	return (ret);
}
