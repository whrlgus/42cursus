#include "get_next_line.h"
#define BUFFER_SIZE 1


size_t	ft_strlen(const char *s)
{
	size_t ret;
	
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
	return ret;
}

t_buffer *find_buffer(t_buffer *buffer, int fd)
{
	if(buffer->fd == fd)
		return buffer;
	if(!buffer->next)
		return buffer->next = new_buffer(fd);
	return find_buffer(buffer->next, fd);
}

int resize(char **line, size_t len)
{
	char *new_line;
	size_t i;
	
	if(!(new_line = malloc(len + BUFFER_SIZE + 1)))
		return 0;
	i = 0;
	while (i < len)
	{
		new_line[i] = (*line)[i];
		++i;
	}
	free(*line);
	*line = new_line;
	return 1;
}

int read_buf(t_buffer *buffer, char **line, int *eof)
{
	size_t i;
	size_t j;
	int ret;
	
	
	
	if (*line){
		i = ft_strlen(*line);
		if(!resize(line, i))
			return -1;
	}
	else
	{
		i = 0;
		*line = malloc(BUFFER_SIZE + 1);
	}
	ret = 0;
	j = 0;
	while (buffer->buf[j])
	{
		(*line)[i++] = buffer->buf[j];
		if (buffer->buf[j++] == '\n')
		{
			*eof = 0;
			--i;
			ret = 1;
			break;
		}
	}
	(*line)[i] = 0;
	i = 0;
	while (buffer->buf[j])
		buffer->buf[i++] = buffer->buf[j++];
	buffer->buf[i] = 0;
	return ret;
}

int get_next_line(int fd, char **line)
{
	static t_buffer *head;
	t_buffer *buffer;
	ssize_t read_size;
	int found;
	int eof;
	
	if (BUFFER_SIZE <= 0 || !line)
	return -1;
	
	eof = 1;

	*line = 0;
	if((!head && !(head = new_buffer(fd))) || !(buffer = find_buffer(head, fd))
	   || (found = read_buf(buffer, line, &eof)) == -1)
		return -1;
	
	if (found)
		return 1;
	
	
	while((read_size = read(fd,buffer->buf,BUFFER_SIZE))){
		if(read_size == -1)
			return -1;
		buffer->buf[read_size] = 0;
		if((found = read_buf(buffer, line, &eof)) == -1)
			return -1;
		if(found)
			return 1;
	}
	return !eof;
}
