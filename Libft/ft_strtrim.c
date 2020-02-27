#include "libft.h"

static int	isIncluded(char a, char const *set)
{
	while (*set)
		if(a == *set++)
			return (1);
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*ret;
	char	*begin;
	char	*until;
	size_t	len;
	
	begin = (char*)s1;
	until = begin + ft_strlen(s1);
	while (*begin && isIncluded(*begin, set))
		++begin;
	while (begin < until && isIncluded(*(until - 1), set))
		--until;
	len = until - begin + 1;
	if(!(ret = malloc(len)))
		return (0);
	ft_strlcpy(ret, begin, len);
	return (ret);
}
