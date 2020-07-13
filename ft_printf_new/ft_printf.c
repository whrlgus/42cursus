#include "ft_printf.h"

char			*g_specifier = "cspdiuxX%";
char			*g_base_10 = "0123456789";
char			*g_base_16_l = "0123456789abcdef";
char			*g_base_16_u = "0123456789ABCDEF";
t_fmt_info		*g_fmt_info;
va_list			g_ap;

char*			get_format_string(void)
{
	char t;
	char *format_str;

	t = g_fmt_info->type;
	if (t == 'c')
		set_conv_c(&format_str, va_arg(g_ap, int));
	else if (t == 's')
		set_conv_s(&format_str);
	else if (t == 'u')
		set_conv_uxX(&format_str, g_base_10);
	else if (t == 'x')
		set_conv_uxX(&format_str, g_base_16_l);
	else if (t == 'X')
		set_conv_uxX(&format_str, g_base_16_u);
	else if (t == 'p')
		set_conv_p(&format_str);
	else if (t == 'd' || t == 'i')
		set_conv_di(&format_str);
	else
		set_conv_c(&format_str, t);
	return format_str;
}

static void		init_format_info(void)
{
	g_fmt_info->minus = 0;
	g_fmt_info->zero = 0;
	g_fmt_info->width = 0;
	g_fmt_info->precision = -1;
	g_fmt_info->type = 0;
}

void			parse(const char *fmt, size_t *len)
{
	char *str;
	
	while (*fmt)
		if (*fmt == '%')
		{
			++fmt;
			init_format_info();
			while (read_flags(&fmt) || read_width(&fmt) ||
			read_precision(&fmt))
				;
			g_fmt_info->type = *(fmt++);
			str = get_format_string();
			*len += ft_strlen(str);
			ft_putstr_fd(str, 1);
			free(str);
			str = 0;
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
	g_fmt_info = malloc(sizeof(t_fmt_info));
	va_start(g_ap, fmt);
	parse(fmt, &ret);
	va_end(g_ap);
	free(g_fmt_info);
	return ((int)ret);
}
