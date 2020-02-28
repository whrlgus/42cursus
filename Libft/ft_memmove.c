#include "libft.h"

void *ft_memmove(void *dst, const void *src, size_t n)
{
	void *ret;
	
	ret = dst;
	if (src < dst)
	{
		src += n;
		dst += n;
		while (n--)
			*(char*)--dst = *(char*)--src;
	}
	else
		while (n--)
			*(char*)dst++ = *(char*)src++;
	return (ret);
}
