#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	size_t	i;
	char	*ret;
	
	len = ft_strlen(s);
	if(!(ret = malloc(len + 1)))
		return (0);
	i = 0;
	while (len--)
		ret[i++] = *s++;
	return (ret);
}
