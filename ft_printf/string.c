/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 22:30:14 by gicho             #+#    #+#             */
/*   Updated: 2020/07/11 22:30:14 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void pad(char **str, size_t *len)
{
	long long	cnt;
	char		c;

	if (g_info->width > (long long)*len)
	{
		cnt = g_info->width - *len;
		c = ((g_info->minus || !g_info->zero) ? ' ' : '0');
		append_chars(str, c, cnt, !g_info->minus);
		*len += cnt;
	}
}

size_t print_character(void)
{
	char	*str;
	size_t	len;

	str = malloc(2);
	str[0] = va_arg(g_ap, int);
	str[1] = 0;
	len = 1;
	pad(&str, &len);
	ft_putstr_fd(str, 1);
	free(str);
	return (len);
}

size_t print_string(void)
{
	char	*str;
	size_t	len;

	str = va_arg(g_ap, char*);
	if(str == 0)
		str = "(null)";
	if (g_info->precision != -1)
		str = ft_substr(str, 0, g_info->precision);
	else
		str = ft_strjoin(str, "");
	len = ft_strlen(str);
	pad(&str, &len);
	ft_putstr_fd(str, 1);
	free(str);
	return (len);
}

size_t print_invalid_type(void)
{
	char	*str;
	size_t	len;

	str = malloc(sizeof(char) * 2);
	str[0] = g_info->type;
	str[1] = 0;
	len = 1;
	pad(&str, &len);
	ft_putstr_fd(str, 1);
	free(str);
	return (len);
}
