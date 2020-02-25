#include "libft.h"

void *ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	while (n--)
	{
		*(char*)dst++ = *(char*)src;
		if (*(char*)src++ == (unsigned char)c)
			return dst;
	}
	return 0;
}
