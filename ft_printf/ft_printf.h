#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
#include "/Users/gihyun/github/42cursus/Libft/libft.h"

typedef struct	s_format_info{
	int 		minus;
	int 		plus;
	int 		space;
	int 		zero;
	int 		hash;
	int 		width;
	int 		precision;
	int			length;
	char		type;
}				t_fmt_info;



int ft_printf(const char *, ...);
size_t print_format_string(void);
void pad_space_for_i(char **str, size_t *len);
#endif
