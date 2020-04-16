#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

//#define BUFFER_SIZE 1

# include<stdlib.h>
# include<unistd.h>

typedef struct s_buffer
{
	int fd;
	char *buf;
	struct s_buffer *next;
}t_buffer;


size_t	ft_strlen(const char *s);
t_buffer *new_buffer(int fd);
t_buffer *find_buffer(t_buffer *buffer, int fd);
int resize(char **line, size_t len);
int get_next_line(int fd, char **line);

#endif
