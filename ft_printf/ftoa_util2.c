/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftoa_util2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 22:30:14 by gicho             #+#    #+#             */
/*   Updated: 2020/07/11 22:30:14 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char *next(char *str, int num)
{
	char	*ret;
	int		i;
	int		carry;
	int		tmp;

	ret = malloc(ft_strlen(str) + 2);
	i = 0;
	carry = 0;
	while (str[i])
	{
		tmp = (str[i] - '0') * num + carry;
		ret[i] = (tmp % 10) + '0';
		carry = tmp / 10;
		++i;
	}
	free(str);
	ret[i++] = carry + '0';
	ret[i] = 0;
	return (ret);
}

char *alloc_str(char c)
{
	char *ret;

	ret = malloc(2);
	ret[0] = c;
	ret[1] = 0;
	return (ret);
}

char *add(char *a, char *b)
{
	char	*ret;
	int		i;
	int		carry;
	int		tmp;

	ret = malloc(ft_strlen(a) + 2);
	i = 0;
	carry = 0;
	while(b[i])
	{
		tmp = (a[i] - '0' + b[i] - '0' + carry);
		ret[i++] = (tmp % 10) + '0';
		carry = tmp / 10;
	}
	while(a[i])
	{
		tmp = (a[i] - '0' + carry);
		ret[i++] = (tmp % 10) + '0';
		carry = tmp / 10;
	}
	if (carry)
		ret[i++] = carry + '0';
	ret[i] = 0;
	return (ret);
}

void str_rev(char *str)
{
	char *ptr;
	char tmp;

	ptr = str + ft_strlen(str) - 1;
	while (str < ptr)
	{
		tmp = *ptr;
		*ptr = *str;
		*str = tmp;
		++str;
		--ptr;
	}
}

void trim_right(char *str)
{
	int i;

	i = (int)ft_strlen(str) - 1;
	while (i >= 0 && str[i] == '0')
		str[i--] = 0;
}
