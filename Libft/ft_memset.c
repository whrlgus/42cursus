#include "libft.h"

void	*ft_memset(void *b, int c, size_t n)
{
	void *ret;

	ret = b;
	while (n--)
		*(char*)b++ = (unsigned char)c;
	return (ret);
}
