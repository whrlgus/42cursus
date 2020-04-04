/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho </var/mail/gicho>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/04 12:55:19 by gicho             #+#    #+#             */
/*   Updated: 2020/04/04 12:55:20 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int ft_isalpha(int c)
{
	return (('a'<= c && c <= 'z') || ('A'<= c && c <= 'Z'));
}
