#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*a;
	char	*b;
	size_t	len_neddle;

	if (!*needle)
		return ((char*)haystack);
	len_neddle = ft_strlen(needle);
	if (len <= len_neddle)
		return (0);
	len -= --len_neddle;
	while (len-- || !*haystack)
	{
		a = (char*)haystack;
		b = (char*)needle;
		while (*b && *a == *b)
		{
			++a;
			++b;
		}
		if (*b == 0)
			return ((char*)haystack);
		++haystack;
	}
	return (0);
}
