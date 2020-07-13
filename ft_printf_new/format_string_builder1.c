/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_string_builder1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 21:48:14 by gicho             #+#    #+#             */
/*   Updated: 2020/07/13 21:48:14 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		pad(char **str, int cnt)
{
	char	*left;
	char	*right;

	if (g_fmt_info->minus)
	{
		left = *str;
		right = string(' ', cnt);
	}
	else
	{
		left = string(g_fmt_info->zero ? '0' : ' ', cnt);
		right = *str;
	}
	*str = ft_strjoin_with_dealloc(left, right);
}

void			set_conv_c(char **str, char c)
{
	int cnt;
	
	*str = malloc(2);
	(*str)[0] = c;
	(*str)[1] = 0;
	cnt = g_fmt_info->width - 1;
	if (cnt > 0)
		pad(str, cnt);
}

void			set_conv_s(char **str)
{
	int cnt;
	
	*str = va_arg(g_ap, char*);
	if (*str == 0)
		*str = "(null)";
	if (g_fmt_info->precision != -1)
		*str = ft_substr(*str, 0, g_fmt_info->precision);
	else
		*str = ft_strjoin(*str, "");
	cnt = g_fmt_info->width - (int)ft_strlen(*str);
	if (cnt > 0)
		pad(str, cnt);
}
