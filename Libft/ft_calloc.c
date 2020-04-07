#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void *ret;
	
	if(!(ret = malloc(count * size)))
		return (0);
	ft_bzero(ret, count * size);
	return (ret);
}
