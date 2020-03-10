#include "ft_printf.h"

static long long read_arg(void)
{
	if (g_info->length == 3)
		return va_arg(g_ap, long long);
	else if (g_info->length == 2)
		return (long)va_arg(g_ap, long);
	else if (g_info->length == 1)
		return (short)va_arg(g_ap, int);
	else if (g_info->length == 0)
		return (char)va_arg(g_ap, int);
	else
		return (int)va_arg(g_ap, int);
}

static void pad_zero(char **str, size_t *len, int neg)
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
	else
	{
		if (!g_info->minus && g_info->zero && g_info->width > (long long)*len)
		{
			cnt = g_info->width - *len;
			if (neg || g_info->plus || g_info->space)
				--cnt;
			append_chars(str, '0', cnt, 1);
			*len += cnt;
		}
	}
}

static void add_sign(char **str, size_t *len, int neg)
{
	char sign;
	
	if (neg || g_info->plus || g_info->space)
	{
		if (neg)
			sign = '-';
		else
			sign = g_info->plus ? '+' : ' ';
		append_chars(str, sign, 1, 1);
		++(*len);
	}
}

size_t print_signed_integer(void)
{
	long long num;
	char *str;
	size_t len;
	int neg;
	
	num = read_arg();
	neg = (num < 0);
	str = neg ? utoa(-num, g_base_10): utoa(num, g_base_10);
	if (num == 0 && g_info->precision == 0)
		str[0] = 0;
	len = ft_strlen(str);
	pad_zero(&str, &len, neg);
	add_sign(&str, &len, neg);
	pad_space_for_i(&str, &len);
	ft_putstr_fd(str, 1);
	free(str);
	return (len);
}
