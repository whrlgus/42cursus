/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 21:57:51 by gicho             #+#    #+#             */
/*   Updated: 2020/04/16 21:57:51 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int read_buf(t_buffer *buffer, char **line)
{
	size_t	i;
	size_t	j;
	int		found;
	
	i = ft_strlen(*line);
	if(!resize(line, i))
		return (-1);
	found = 0;
	j = 0;
	while (buffer->buf[j])
	{
		(*line)[i++] = buffer->buf[j];
		if (buffer->buf[j++] == '
')
		{
			--i;
			found = 1;
			break;
		}
	}
	(*line)[i] = 0;
	i = 0;
	while (buffer->buf[j])
		buffer->buf[i++] = buffer->buf[j++];
	buffer->buf[i] = 0;
	return (found);
}

int get_next_line(int fd, char **line)
{
	static t_buffer	*head;
	t_buffer		*buffer;
	int				size;
	int				found;
	
	if (BUFFER_SIZE <= 0 || !line
		|| (!head && !(head = new_buffer(fd)))
		|| !(buffer = find_buffer(head, fd)))
		return (-1);
	*line = 0;
	if ((found = read_buf(buffer, line)))
		return (found);
	while((size = read(fd,buffer->buf,BUFFER_SIZE))>0){
		buffer->buf[size] = 0;
		if ((found = read_buf(buffer, line)))
			return (found);
	}
	return (size);
}
