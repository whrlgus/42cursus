/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 12:43:43 by gicho             #+#    #+#             */
/*   Updated: 2020/10/24 12:43:43 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utility.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int s1_len;
	int s2_len;

	s1_len = (int)ft_strlen(s1);
	s2_len = (int)ft_strlen(s2);
	if (s1_len != s2_len)
		return (s1_len - s2_len);
	return (ft_strncmp(s1, s2, s1_len));
}
