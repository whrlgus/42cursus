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
		left = string(g_fmt_info->zero && g_fmt_info->precision == -1 ? '0' : ' ', cnt);
		right = *str;
	}
	*str = ft_strjoin_with_dealloc(left, right);
}

void			set_conv_uxX(char **str, char *base)
{
	int				cnt;
	unsigned int	num;

	num = va_arg(g_ap, unsigned int);
	*str = utoa(num, base);
	if (num == 0 && g_fmt_info->precision == 0)
		(*str)[0] = 0;
	cnt = g_fmt_info->precision - (int)ft_strlen(*str);
	if (cnt > 0)
		pad_with_leading_zeros(str, cnt);
	cnt = g_fmt_info->width - (int)ft_strlen(*str);
	if (cnt > 0)
		pad(str, cnt);
}
