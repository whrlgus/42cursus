#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char *ret;
	
	ret = 0;
	while (1)
	{
		if (*s == (unsigned char)c)
			ret = (char*)s;
		if(*s == 0)
			break ;
		++s;
	}
	return (ret);
}
