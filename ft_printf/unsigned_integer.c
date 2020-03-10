#include "ft_printf.h"

static unsigned long long read_arg(void)
{
	if (g_info->length == 3)
		return va_arg(g_ap, unsigned long long);
	else if (g_info->length == 2)
		return (unsigned long)va_arg(g_ap, unsigned long);
	else if (g_info->length == 1)
		return (unsigned short)va_arg(g_ap, unsigned int);
	else if (g_info->length == 0)
		return (unsigned char)va_arg(g_ap, unsigned int);
	else
		return (unsigned int)va_arg(g_ap, unsigned int);
}

static void pad_zero(char **str, size_t *len)
{
	long long cnt;
	
	if (g_info->precision >= 0)
	{
		if (g_info->precision > (long long)*len)
		{
			cnt = g_info->precision - *len;
			append_chars(str, '0', cnt, 1);
			*len += cnt;
		}
	}
	else if (g_info->zero && g_info->width > (long long)*len)
	{
		cnt = g_info->width - *len;
		if (g_info->type != 'u' && g_info->hash)
			cnt -= 2;
		if (cnt > 0)
		{
			append_chars(str, '0', cnt, 1);
			*len += cnt;
		}
	}
}

static void add_prefix(char **str, size_t *len)
{
	char c;
	
	if (g_info->hash && (g_info->type == 'x' || g_info->type == 'X'))
	{
		c = (g_info->type == 'x' ? 'x' : 'X');
		append_chars(str, c, 1, 1);
		append_chars(str, '0', 1, 1);
		*len += 2;
	}
}

size_t print_unsigned_integer(void)
{
	unsigned long long num;
	char *str;
	size_t len;
	
	num = read_arg();
	if(g_info->type=='u')
		str = utoa(num, g_base_10);
	else if(g_info->type=='x')
		str = utoa(num, g_base_16_l);
	else
		str = utoa(num, g_base_16_u);
	if (num == 0 && g_info->precision == 0)
		str[0] = 0;
	len = ft_strlen(str);
	if (num == 0)
		g_info->hash = 0;
	pad_zero(&str, &len);
	add_prefix(&str, &len);
	pad_space_for_i(&str, &len);
	ft_putstr_fd(str, 1);
	free(str);
	return (len);
}

size_t print_pointer(void)
{
	char *str;
	size_t len;
	
	g_info->hash = 1;
	g_info->type = 'x';
	str = utoa((long long)va_arg(g_ap, void*), g_base_16_l);
	len = ft_strlen(str);
	pad_zero(&str, &len);
	add_prefix(&str, &len);
	pad_space_for_i(&str, &len);
	ft_putstr_fd(str, 1);
	free(str);
	return (len);
}

