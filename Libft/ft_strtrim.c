/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 11:36:07 by gicho             #+#    #+#             */
/*   Updated: 2020/04/08 11:36:07 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isincluded(char a, char const *set)
{
	while (*set)
		if (a == *set++)
			return (1);
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*ret;
	char	*begin;
	char	*until;
	size_t	len;

	begin = (char*)s1;
	until = begin + ft_strlen(s1);
	while (*begin && isincluded(*begin, set))
		++begin;
	while (begin < until && isincluded(*(until - 1), set))
		--until;
	len = until - begin + 1;
	if (!(ret = malloc(len)))
		return (0);
	ft_strlcpy(ret, begin, len);
	return (ret);
}
