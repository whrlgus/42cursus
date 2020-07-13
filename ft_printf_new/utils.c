#include "ft_printf.h"

char*		string(char c, int cnt)
{
	char *str;
	
	str = malloc(cnt + 1);
	str[cnt] = 0;
	while (cnt--)
		str[cnt] = c;
	return (str);
}

static int	get_nbr_len(long long num, int base_len)
{
	return num ? 1 + get_nbr_len(num / base_len, base_len) : 0;
}

char		*utoa(long long num, const char *base)
{
	int len;
	char *ret;
	int base_len;

	base_len = (int)ft_strlen(base);
	len = 1 + get_nbr_len(num / base_len, base_len);
	ret = malloc(len + 1);
	ret[len] = 0;
	while(--len >= 0)
	{
		ret[len] = base[(num % base_len)];
		num /= base_len;
	}
	return (ret);
}

void		pad_with_leading_zeros(char **str, int cnt)
{
	char *left;
	char *right;
	
	left = string('0', cnt);
	right = *str;
	*str = ft_strjoin_with_dealloc(left, right);
}

char*		ft_strjoin_with_dealloc(char *a, char *b)
{
	char	*ret;
	
	ret = ft_strjoin(a, b);
	free(a);
	free(b);
	return (ret);
}
