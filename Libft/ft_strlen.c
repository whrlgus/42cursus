#include "libft.h"
size_t	ft_strlen(const char *s)
{
	size_t ret;
	
	ret = 0;
	while (*s++)
		++ret;
	return (ret);
}
