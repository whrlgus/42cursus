/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_infomation_reader.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 21:48:14 by gicho             #+#    #+#             */
/*   Updated: 2020/07/13 21:48:14 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		read_flags(const char **fmt)
{
	char c;

	c = **fmt;
	if (c == '-')
		g_fmt_info->minus = 1;
	else if (c == '0')
		g_fmt_info->zero = 1;
	else
		return (0);
	++(*fmt);
	return (1);
}

int		read_width(const char **fmt)
{
	char c;

	c = **fmt;
	if (c == '*')
	{
		g_fmt_info->width = va_arg(g_ap, int);
		if (g_fmt_info->width < 0)
		{
			g_fmt_info->minus = 1;
			g_fmt_info->width *= -1;
		}
		++(*fmt);
	}
	else if (ft_isdigit(c))
	{
		g_fmt_info->width = ft_atoi(*fmt);
		while (ft_isdigit(**fmt))
			++(*fmt);
	}
	else
		return (0);
	return (1);
}

int		read_precision(const char **fmt)
{
	char c;

	if (**fmt != '.')
		return (0);
	c = *(++(*fmt));
	g_fmt_info->precision = 0;
	if (c == '*')
	{
		g_fmt_info->precision = va_arg(g_ap, int);
		++(*fmt);
	}
	else if(ft_isdigit(c))
	{
		g_fmt_info->precision = ft_atoi(*fmt);
		while (ft_isdigit(**fmt))
			++(*fmt);
	}
	return (1);
}
