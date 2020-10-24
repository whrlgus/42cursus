/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 12:43:43 by gicho             #+#    #+#             */
/*   Updated: 2020/10/24 12:43:43 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fileio.h"

int	is_valid_file_name(char *file_path)
{
	int		len;
	char	*ext;
	int		cmp_result;

	if ((len = (int)ft_strlen(file_path)) < 4)
		return (0);
	ext = ft_substr(file_path, len - 4, 4);
	cmp_result = ft_strncmp(ext, ".cub", 4);
	free(ext);
	return (cmp_result == 0);
}

int	read_file(char *file_path, t_string_array *str_arr)
{
	int		fd;
	char	*line;
	int		gnl_ret_val;

	if (!is_valid_file_name(file_path))
		return (print_error(cuberror(invalid_file_name)));
	else if ((fd = open(file_path, O_RDONLY)) == -1)
		return (print_error(strerror(errno)));
	while ((gnl_ret_val = get_next_line(fd, &line)))
	{
		if (gnl_ret_val == -1)
			return (print_error(cuberror(gnl_error)));
		if ((append(str_arr, line) == -1))
			return (print_error(strerror(errno)));
		free(line);
	}
	close(fd);
	free(line);
	return (0);
}
