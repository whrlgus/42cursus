/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 12:43:43 by gicho             #+#    #+#             */
/*   Updated: 2020/10/24 12:43:43 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

char	*cuberror(enum e_error type)
{
	if (type == invalid_file_name)
		return ("invalid cub file name");
	else if (type == invalid_config_format)
		return ("invalid configuration");
	else if (type == invlid_texture_file)
		return ("invalid texture file");
	else if (type == invalid_argument)
		return ("invalid argument");
	return ("");
}

int		print_error(char *msg)
{
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(msg, 2);
	return (-1);
}
