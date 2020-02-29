#include "libft.h"

void *ft_memchr(const void *s, int c, size_t n)
{
	while (n--)
	{
		if (*(unsigned char*)s==(unsigned char)c)
			return ((void*)s);
		++s;
	}
	return (0);
}

