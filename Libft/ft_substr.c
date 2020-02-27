#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	
	if (!(ret = malloc(++len)))
		return (0);
	ft_strlcpy(ret, s + start, len);
	return (ret);
}
