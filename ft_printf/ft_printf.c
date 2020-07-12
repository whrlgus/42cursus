/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 22:30:14 by gicho             #+#    #+#             */
/*   Updated: 2020/07/11 22:30:14 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

const char	*g_base_10;
const char	*g_base_16_l;
const char	*g_base_16_u;
const char	*g_specifier;
t_fmt_info	*g_info;
va_list		g_ap;

static void		init_format_info(void)
{
	g_info->minus = 0;
	g_info->plus = 0;
	g_info->space = 0;
	g_info->hash = 0;
	g_info->zero = 0;
	g_info->width = 0;
	g_info->precision = -1;
	g_info->length = -1;
	g_info->type = 0;
}

static size_t	print_format_string(void)
{
	char t;

	t = g_info->type;
	if (t == 'd' || t == 'i')
		return (print_signed_integer());
	else if (t == 'u' || t == 'x' || t == 'X')
		return (print_unsigned_integer());
	else if (t == 'f' || t == 'e' || t == 'g')
		return (print_real_number());
	else if (t == 'c')
		return (print_character());
	else if (t == 's')
		return (print_string());
	else if (t == 'p')
		return (print_pointer());
	else
		return (print_invalid_type());
}

static void		parse(const char *fmt, size_t *len)
{
	while (*fmt)
		if (*fmt == '%')
		{
			++fmt;
			init_format_info();
			while (read_flags(&fmt) || read_width(&fmt) ||
			read_precision(&fmt) || read_length(&fmt))
				;
			g_info->type = *(fmt++);
			if (g_info->type == 'n')
				write_num_of_chars(*len);
			else if (g_info->type)
				*len += print_format_string();
		}
		else
		{
			ft_putchar_fd(*fmt++, 1);
			++(*len);
		}
}

int				ft_printf(const char *fmt, ...)
{
	size_t ret;

	ret = 0;
	g_base_10 = "0123456789";
	g_base_16_l = "0123456789abcdef";
	g_base_16_u = "0123456789ABCDEF";
	g_specifier = "cspdiuxX%nfge";
	g_info = malloc(sizeof(t_fmt_info));
	va_start(g_ap, fmt);
	parse(fmt, &ret);
	free(g_info);
	va_end(g_ap);
	return ((int)ret);
}
