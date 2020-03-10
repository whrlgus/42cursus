#ifndef FT_NORMALIZE_H
# define FT_NORMALIZE_H

#include "/Users/gihyun/github/42cursus/Libft/libft.h"
#include "ft_printf.h"

typedef struct s_real_num
{
	int exp;
	char *bits;
}	t_real_num;

int		max(int a, int b);
void	swap(char **a, char **b);
char	*init(char c);
char	*add(char *a, char *b);
char	*next(char *str, int num);

void normalize(double num);

#endif
