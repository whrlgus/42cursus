/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 22:20:09 by gicho             #+#    #+#             */
/*   Updated: 2020/04/16 22:20:09 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFFER_SIZE 80

# include <stdlib.h>
# include <unistd.h>

typedef struct		s_buffer
{
	int				fd;
	char			buf[BUFFER_SIZE + 1];
	struct s_buffer	*next;
}					t_buffer;

size_t				ft_strlen_gnl(const char *s);
t_buffer			*new_buffer(int fd);
t_buffer			*find_buffer(t_buffer *buffer, int fd);
void				remove_buffer(t_buffer **head, int fd);
int					resize(char **line, size_t len);
int					get_next_line(int fd, char **line);
#endif
