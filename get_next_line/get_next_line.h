#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include<stdlib.h>
# include<unistd.h>

typedef struct s_buffer
{
	int fd;
	char *buf;
	struct s_buffer *next;
}t_buffer;

int get_next_line(int fd, char **line);

#endif
