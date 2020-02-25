#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	while (n--)
	{
		if(*(char*)s1 != *(char*)s2)
			return (unsigned char)*(char*)s1 - (unsigned char)*(char*)s2;
		++s1;
		++s2;
	}
	return 0;
}
