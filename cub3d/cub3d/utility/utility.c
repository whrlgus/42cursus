/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 12:43:43 by gicho             #+#    #+#             */
/*   Updated: 2020/10/24 12:43:43 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utility.h"

int		append(t_string_array *str_arr, char *str)
{
	char	**ele;
	int		i;

	if (!(ele = (char **)malloc(sizeof(char *) * (str_arr->size + 1))))
		return (-1);
	i = 0;
	while (i < str_arr->size)
	{
		ele[i] = str_arr->ele[i];
		++i;
	}
	ele[i] = ft_strjoin(str, "");
	free(str_arr->ele);
	str_arr->size += 1;
	str_arr->ele = ele;
	return (0);
}

int		count_token(char **token)
{
	int i;

	i = 0;
	while (token[i])
		++i;
	return (i);
}

int		is_included(char c, char *set)
{
	while (*set)
		if (c == *set++)
			return (1);
	return (0);
}

int		count_chars(const char *s, int c)
{
	int cnt;

	cnt = 0;
	while (*s)
	{
		if (*s == c)
			++cnt;
		++s;
	}
	return (cnt);
}

void	free_2d_arr(char **arr, int size)
{
	int i;

	i = 0;
	while (i < size)
		free(arr[i++]);
	free(arr);
}
