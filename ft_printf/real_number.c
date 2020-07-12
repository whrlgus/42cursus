/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   real_number.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 22:30:14 by gicho             #+#    #+#             */
/*   Updated: 2020/07/11 22:30:14 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_nrm	*g_nrm;

void	add_sign(void)
{
	if (g_nrm->neg)
		append_chars(&g_nrm->str, '-', 1, 1);
	else if (g_info->plus)
		append_chars(&g_nrm->str, '+', 1, 1);
	else if (g_info->space)
		append_chars(&g_nrm->str, ' ', 1, 1);
}

void	normalize(double num, char *str_int, char *str_fra)
{
	if (num == 0)
	{
		g_nrm->exp = 0;
		g_nrm->str = alloc_str('0');
	}
	else
	{
		g_nrm->neg = (num < 0);
		if (*str_int)
		{
			g_nrm->exp = (int)ft_strlen(str_int) -1;
			g_nrm->str = ft_strjoin(str_int, str_fra);
		}
		else
		{
			g_nrm->exp = 0;
			while (str_fra[g_nrm->exp]=='0')
				++g_nrm->exp;
			g_nrm->str = ft_substr(str_fra, g_nrm->exp, ft_strlen(str_fra) - g_nrm->exp);
			g_nrm->exp = -g_nrm->exp - 1;
		}
	}
}

size_t	scientific(void)
{
	int tmp;

	tmp = g_info->precision - (int)ft_strlen(g_nrm->str) + 1;
	if (tmp >= 0)
		append_chars(&g_nrm->str, '0', tmp, 0);
	else
	{
		round_num(&g_nrm->str, g_info->precision + 1);
		g_nrm->str[g_info->precision + 1] = 0;
	}
	insert_decimal_point();
	append_suffix(&g_nrm->str);
	pad_zero();
	add_sign();
	pad_space();
	ft_putstr_fd(g_nrm->str, 1);
	return (ft_strlen(g_nrm->str));
}

size_t	decimal_fp(void)
{
	char	*str;
	int		tmp;

	str = 0;
	tmp = g_info->precision - (int)ft_strlen(g_nrm->str);
	if (tmp >= 0)
		append_chars(&g_nrm->str, '0', tmp, 0);
	else
	{
		round_num(&g_nrm->str, g_info->precision + 1);
		g_nrm->str[g_info->precision + 1] = 0;
	}
	pad_zero();
	add_sign();
	pad_space();
	ft_putstr_fd(str, 1);
	return (10);
}

size_t	print_real_number(void)
{
	double	num;
	char	*str_int;
	char	*str_fra;
	size_t	ret;

	num = va_arg(g_ap, double);
	ft_ftoa(num, &str_int, &str_fra);
	if (g_info->precision == -1)
		g_info->precision = 6;
	ret=0;
	if(g_info->type == 'e')
	{
		g_nrm = malloc(sizeof(t_nrm));
		normalize(num, str_int, str_fra);
		ret = scientific();
		free(g_nrm->str);
		free(g_nrm);
	}
	else if(g_info->type == 'f')
	{
		
		ret = decimal_fp();
	}
	free(str_int);
	free(str_fra);
	return (ret);
}
