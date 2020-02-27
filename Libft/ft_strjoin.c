#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*ret;
	
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	ret = malloc(len);
	ft_strlcpy(ret, s1, len);
	ft_strlcat(ret, s2, len);
	return (ret);
}
