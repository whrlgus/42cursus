/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_string_builder3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 21:48:14 by gicho             #+#    #+#             */
/*   Updated: 2020/07/13 21:48:14 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		pad_zero(char **str, int neg)
{
	int cnt;
	int len;

	len = (int)ft_strlen(*str);
	if (g_fmt_info->precision >= 0)
	{
		cnt = g_fmt_info->precision - len;
		if (cnt > 0)
			*str = ft_strjoin_with_dealloc(string('0', cnt), *str);
	}
	else
	{
		cnt = g_fmt_info->width - len;
		if (!g_fmt_info->minus && g_fmt_info->zero && cnt > 0)
			*str = ft_strjoin_with_dealloc(string('0', cnt - neg), *str);
	}
}

static void		add_sign(char **str)
{
	char *tmp;
	
	tmp = *str;
	*str = ft_strjoin("-", *str);
	free(tmp);
}

void			pad_space(char **str)
{
	int cnt;

	cnt = g_fmt_info->width - (int)ft_strlen(*str);
	if (cnt > 0)
	{
		if (g_fmt_info->minus)
			*str = ft_strjoin_with_dealloc(*str, string(' ', cnt));
		else
			*str = ft_strjoin_with_dealloc(string(' ', cnt), *str);
	}
}

void			set_conv_di(char **str)
{
	long long	num;
	size_t		len;
	int			neg;

	num = va_arg(g_ap, int);
	neg = (num < 0);
	*str = neg ? utoa(-num, g_base_10): utoa(num, g_base_10);
	if (num == 0 && g_fmt_info->precision == 0)
		(*str)[0] = 0;
	len = ft_strlen(*str);
	pad_zero(str, neg);
	if (neg)
		add_sign(str);
	pad_space(str);
}
