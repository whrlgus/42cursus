/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_fmt_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 22:30:14 by gicho             #+#    #+#             */
/*   Updated: 2020/07/11 22:30:14 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int read_specifier(const char **fmt)
{
	const char *ptr;

	ptr = g_specifier;
	while (*ptr)
	{
		if (**fmt==*ptr)
		{
			g_info->type = *((*fmt)++);
			return (1);
		}
		++ptr;
	}
	return (0);
}

int read_flags(const char **fmt)
{
	char c;

	c = **fmt;
	if (c == '-')
		g_info->minus = 1;
	else if (c == '+')
		g_info->plus = 1;
	else if (c == ' ')
		g_info->space = 1;
	else if (c == '#')
		g_info->hash = 1;
	else if (c == '0')
		g_info->zero = 1;
	else
		return (0);
	++(*fmt);
	return (1);
}

int read_width(const char **fmt)
{
	char c = **fmt;

	if (c == '*'){
		g_info->width = va_arg(g_ap, int);
		if (g_info->width < 0)
		{
			g_info->minus = 1;
			g_info->width *= -1;
		}
		++(*fmt);
	}else if(ft_isdigit(c)){
		g_info->width = ft_atoi(*fmt);
		while (ft_isdigit(**fmt))
			++(*fmt);
	}else
		return (0);
	return (1);
}

int read_precision(const char **fmt)
{
	char c;

	if(**fmt != '.')
		return (0);
	c = *(++(*fmt));
	g_info->precision = 0;
	if (c == '*'){
		g_info->precision = va_arg(g_ap, int);
		++(*fmt);
	}else if(ft_isdigit(c)){
		g_info->precision = ft_atoi(*fmt);
		while (ft_isdigit(**fmt))
			++(*fmt);
	}
	return (1);
}

int read_length(const char **fmt)
{
	if (**fmt == 'h')
	{
		if (g_info->length < 0 && *(*fmt + 1) && *(*fmt + 1) == 'h')
		{
			g_info->length = 0;
			++(*fmt);
		}
		else if (g_info->length < 1)
			g_info->length = 1;
	}
	else if (**fmt == 'l')
	{
		if (*(*fmt + 1) && *(*fmt + 1) == 'l')
		{
			g_info->length = 3;
			++(*fmt);
		}
		else if (g_info->length < 2)
			g_info->length = 2;
	}
	else
		return (0);
	++(*fmt);
	return (1);
}
