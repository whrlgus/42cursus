/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileio.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 12:43:43 by gicho             #+#    #+#             */
/*   Updated: 2020/10/24 12:43:43 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILEIO_H
# define FILEIO_H

# include <fcntl.h>
# include "utility.h"
# include "error.h"
# include "get_next_line.h"

int read_file(char *file_path, t_string_array *str_arr);
int save_image_to_bmp_file(int **data, int width, int height);

#endif
