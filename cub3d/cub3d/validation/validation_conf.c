/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_conf.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 12:43:43 by gicho             #+#    #+#             */
/*   Updated: 2020/10/24 12:43:43 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"

int	is_all_equal_num(int arr[], int size, int num)
{
	int i;

	i = 0;
	while (i < size)
		if (arr[i++] != num)
			return (0);
	return (1);
}

int	is_valid_conf(t_string_array *conf)
{
	int i;
	int chk[9];

	i = -1;
	ft_memset(chk, 0, sizeof(chk));
	while (++i < conf->size)
	{
		if (!ft_strlen(conf->ele[i]))
			continue ;
		if (is_included(conf->ele[i][0], " 01"))
		{
			if (!is_valid_map(conf, &i, chk))
				return (0);
			break ;
		}
		if (!is_valid_key(conf->ele[i], chk))
			return (0);
	}
	while (++i < conf->size)
		if (ft_strlen(conf->ele[i]))
			return (0);
	return (is_all_equal_num(chk, 9, 1));
}
