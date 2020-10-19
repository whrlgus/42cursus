/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 22:20:09 by gicho             #+#    #+#             */
/*   Updated: 2020/04/16 22:20:09 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t		ft_strlen_gnl(const char *s)
{
	size_t ret;

	if (!s)
		return (0);
	ret = 0;
	while (*s++)
		++ret;
	return (ret);
}

t_buffer	*new_buffer(int fd)
{
	t_buffer *ret;

	if (!(ret = malloc(sizeof(t_buffer))))
		return (0);
	ret->fd = fd;
	ret->next = 0;
	ret->buf[0] = 0;
	return (ret);
}

t_buffer	*find_buffer(t_buffer *buffer, int fd)
{
	if (buffer->fd == fd)
		return (buffer);
	if (!buffer->next)
		return (buffer->next = new_buffer(fd));
	return (find_buffer(buffer->next, fd));
}

void		remove_buffer(t_buffer **head, int fd)
{
	t_buffer *prev;
	t_buffer *curr;

	prev = *head;
	if (prev->fd == fd)
	{
		curr = prev->next;
		free(prev);
		*head = curr;
		return ;
	}
	while (prev->next->fd != fd)
		prev = prev->next;
	curr = find_buffer(*head, fd);
	prev->next = curr->next;
	free(curr);
}

int			resize(char **line, size_t len)
{
	char	*new_line;
	size_t	i;

	if (!(new_line = malloc(len + BUFFER_SIZE + 1)))
		return (0);
	i = 0;
	while (i < len)
	{
		new_line[i] = (*line)[i];
		++i;
	}
	new_line[i] = 0;
	free(*line);
	*line = new_line;
	return (1);
}
