#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t i;

	i = 0;
	while (src[i] && i + 1 < dstsize)
	{
		dst[i] = src[i];
		++i;
	}
	dst[i] = 0;
	while (src[i])
		++i;
	return (i);
}
