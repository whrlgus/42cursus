#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t ret;
	
	if (!s)
		return (0);
	ret = 0;
	while (*s++)
		++ret;
	return (ret);
}

t_buffer *new_buffer(int fd)
{
	t_buffer *ret;
	
	if(!(ret = malloc(sizeof(t_buffer))))
		return 0;
	ret->fd = fd;
	ret->next = 0;
	if(!(ret->buf = malloc(BUFFER_SIZE + 1)))
		return 0;
	ret->buf[0]=0;
	return (ret);
}

t_buffer *find_buffer(t_buffer *buffer, int fd)
{
	if(buffer->fd == fd)
		return (buffer);
	if(!buffer->next)
		return (buffer->next = new_buffer(fd));
	return (find_buffer(buffer->next, fd));
}

int resize(char **line, size_t len)
{
	char	*new_line;
	size_t	i;
	
	if(!(new_line = malloc(len + BUFFER_SIZE + 1)))
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
