/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 22:30:14 by gicho             #+#    #+#             */
/*   Updated: 2020/07/11 22:30:14 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ftoa_int(char *bits)
{
	char	*ret;
	char	*num;
	char	*tmp;
	int		i;

	if (!*bits)
		return alloc_str(0);
	ret = alloc_str('0');
	num = alloc_str('1');
	i = (int)ft_strlen(bits);
	while(--i >= 0)
	{
		if (bits[i] == '1')
		{
			tmp = (ft_strlen(ret) > ft_strlen(num) ?
				   add(ret, num) : add(num, ret));
			free(ret);
			ret = tmp;
		}
		num = next(num, 2);
	}
	free(num);
	return (ret);
}

char	*ftoa_fra(char *bits)
{
	char *ret;
	char *num;
	char *tmp;

	if (!*bits)
		return alloc_str(0);
	ret = alloc_str('0');
	num = alloc_str('5');
	while(*bits)
	{
		if (*bits == '1')
		{
			tmp = (ft_strlen(ret) > ft_strlen(num) ? add(ret, num) : add(num, ret));
			free(ret);
			ret = tmp;
		}
		if (*(++bits))
		{
			ret = next(ret, 10);
			num = next(num, 5);
		}
		else
			break;
	}
	free(num);
	return (ret);
}

void	ft_ftoa(double num, char **str_int, char **str_fra)
{
	char	*bits;
	char	*bits_integer;
	char	*bits_fraction;
	int		exp;

	if (num == 0)
	{
		*str_int = alloc_str(0);
		*str_fra = alloc_str(0);
		return ;
	}
	long long tmp;
	tmp = (long long)num;
	bits = get_frac_bits(&tmp);
	exp = get_exp(&tmp);
	bits_integer = get_bits_int(bits, exp);
	bits_fraction = get_bits_fra(bits, exp);
	*str_int = ftoa_int(bits_integer);
	trim_right(*str_int);
	*str_fra = ftoa_fra(bits_fraction);
	str_rev(*str_int);
	str_rev(*str_fra);
	trim_right(*str_fra);
	free(bits);
	free(bits_integer);
	free(bits_fraction);
}
