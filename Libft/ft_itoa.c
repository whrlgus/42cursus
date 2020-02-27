#include "libft.h"

static int	get_len(int n)
{
	return (n == 0 ? 0 : 1 + get_len(n / 10));
}

char		*ft_itoa(int n)
{
	char			*ret;
	int				len;
	unsigned int	tmp;
	
	len = 1 + get_len(n / 10);
	if (n < 0)
	{
		++len;
		tmp = -n;
	}
	else
		tmp = n;
	if(!(ret = malloc(len + 1)))
		return (0);
	ret[len] = 0;
	if (n < 0)
		ret[0] = '-';
	ret[--len] = '0' + (tmp % 10);
	while (tmp /= 10)
		ret[--len] = '0' + (tmp % 10);
	return (ret);
}
