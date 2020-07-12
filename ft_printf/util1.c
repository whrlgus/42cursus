/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 22:30:14 by gicho             #+#    #+#             */
/*   Updated: 2020/07/11 22:30:14 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void append_chars(char **src, char c, long long cnt, int front)
{
	char *tmp;
	char *chars;

	if (cnt <= 0)
		return ;
	chars = malloc(sizeof(char) * (cnt + 1));
	chars[cnt] = 0;
	ft_memset(chars, c, cnt);
	if (front)
		tmp = ft_strjoin(chars, *src);
	else
		tmp = ft_strjoin(*src, chars);
	free(chars);
	free(*src);
	*src = tmp;
}

void pad_space_for_i(char **str, size_t *len)
{
	long long cnt;

	if (g_info->width > (long long)*len)
	{
		cnt = g_info->width - *len;
		append_chars(str, ' ', cnt, !g_info->minus);
		*len += cnt;
	}
}

int get_nbr_len(unsigned long long num, int base_len)
{
	return num ? 1 + get_nbr_len(num / base_len, base_len) : 0;
}

char *utoa(unsigned long long num, const char *base)
{
	int len;
	char *ret;
	int base_len;

	base_len = (int)ft_strlen(base);
	len = 1 + get_nbr_len(num / base_len, base_len);
	ret = malloc(sizeof(char) * (len + 1));
	ret[len] = 0;
	while(--len >= 0)
	{
		ret[len] = base[(num % base_len)];
		num /= base_len;
	}
	return (ret);
}
