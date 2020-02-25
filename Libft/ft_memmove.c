#include "libft.h"

void *ft_memmove(void *dst, const void *src, size_t n)
{
	void *tmp = (void*)malloc(sizeof(void));
	ft_memcpy(tmp, src, n);
	ft_memcpy(dst, tmp, n);
	return dst;
}
