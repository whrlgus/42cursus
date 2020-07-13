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
		if (g_fmt_info->zero && g_fmt_info->precision == -1)
		{
			left = string('0', cnt);
			right = ft_strjoin(left, &(*str)[2]);
			free(left);
			free(*str);
			*str = ft_strjoin("0x", right);
			free(right);
			return ;
		}
		left = string(' ', cnt);
		right = *str;
	}
	*str = ft_strjoin_with_dealloc(left, right);
}

void			set_conv_p(char **str)
{
	int		cnt;
	char	*tmp;

	*str = utoa((long long)va_arg(g_ap, void*), g_base_16_l);
	cnt = g_fmt_info->precision - (int)ft_strlen(*str);
	if (cnt > 0)
		pad_with_leading_zeros(str, cnt);
	tmp = *str;
	*str = ft_strjoin("0x", *str);
	free(tmp);
	cnt = g_fmt_info->width - (int)ft_strlen(*str);
	if (cnt > 0)
		pad(str, cnt);
}
