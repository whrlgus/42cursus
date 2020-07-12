/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   real_number2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 22:30:14 by gicho             #+#    #+#             */
/*   Updated: 2020/07/11 22:30:14 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

extern t_nrm *g_nrm;

void	round_num(char **str, int i)
{
	int		tmp;
	int		carry;
	char	*new_str;

	carry = ((*str)[i] >= '5');
	while (i > 0 && carry)
	{
		tmp = carry + (*str)[--i] - '0';
		(*str)[i] = ((tmp % 10) + '0');
		carry = tmp / 10;
	}
	if (carry)
	{
		new_str = malloc(ft_strlen(*str) + 2);
		new_str[0] = carry + '0';
		new_str[1] = 0;
		new_str = ft_strjoin(new_str, *str);
		free(*str);
		*str = new_str;
	}
}

void	append_suffix(char **str)
{
	char	*new_str;
	char	*suffix;
	int		tmp;
	int		i;

	tmp = (g_nrm->exp < 0 ? -g_nrm->exp : g_nrm->exp);
	i = (tmp / 100 ? 6 : 5);
	suffix = malloc(i);
	suffix[0] = 'e';
	suffix[1] = (g_nrm->exp < 0 ? '-' : '+');
	suffix[--i] = 0;
	while (--i > 1)
	{
		suffix[i] = tmp % 10 + '0';
		tmp /= 10;
	}
	new_str = ft_strjoin(*str, suffix);
	free(*str);
	free(suffix);
	*str = new_str;
}

void	insert_decimal_point(void)
{
	char	*new_str;
	int		len;

	len = (int)ft_strlen(g_nrm->str);
	new_str = malloc(len + 2);
	new_str[0] = g_nrm->str[0];
	new_str[1] = '.';
	new_str[2] = 0;
	ft_strlcat(new_str, g_nrm->str + 1, len + 2);
	free(g_nrm->str);
	g_nrm->str = new_str;
}

void	pad_zero(void)
{
	int len;
	int cnt;

	len = (int)ft_strlen(g_nrm->str);
	if (!g_info->minus && g_info->zero && g_info->width > len)
	{
		cnt = g_info->width - len;
		if (g_nrm->neg || g_info->plus || g_info->space)
			--cnt;
		append_chars(&g_nrm->str, '0', cnt, 1);
	}
}

void	pad_space(void)
{
	int len;
	int cnt;

	len = (int)ft_strlen(g_nrm->str);
	if (g_info->width > len)
	{
		cnt = g_info->width - len;
		append_chars(&g_nrm->str, ' ', cnt, !g_info->minus);
	}
}
