#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void *ret;
	
	ret = dst;
	while(n--)
		*(char*)dst++ = *(char*)src++;
	return (ret);
}
