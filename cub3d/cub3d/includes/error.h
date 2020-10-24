/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 13:09:10 by gicho             #+#    #+#             */
/*   Updated: 2020/10/24 13:09:10 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "libft.h"
# include <string.h>
# include <errno.h>

enum	e_error{
	invalid_file_name,
	gnl_error,
	invalid_config_format,
	invlid_texture_file,
	invalid_argument
};

char	*cuberror(enum e_error type);
int		print_error(char *msg);
#endif
