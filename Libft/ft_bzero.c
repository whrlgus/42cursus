#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	while (n--)
		*(char*)s++ = 0;
}
