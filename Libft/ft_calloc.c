/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho </var/mail/gicho>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/04 12:54:26 by gicho             #+#    #+#             */
/*   Updated: 2020/04/04 12:54:28 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void *ret;
	
	if(!(ret = malloc(count * size)))
		return (0);
	ft_bzero(ret, count * size);
	return (ret);
}
