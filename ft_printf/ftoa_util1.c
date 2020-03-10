#include "ft_printf.h"

int get_exp(long long *num)
{
	int ret;
	int i;
	
	ret = 0;
	i = 63;
	while (--i >= 52)
		ret = (ret<<1) + 1&(*num>>i);
	ret-=((1<<10)-2);
	return (ret);
}

char *get_frac_bits(long long *num)
{
	char *ret;
	int i;

	ret = malloc(54);
	ret[0] = '1';
	ret[53] = 0;
	i = 52;
	while (--i >= 0)
		ret[52 - i] = (1&(*num>>i) ? '1' : '0');
	return (ret);
}

char *get_bits_int(char *bits, int exp)
{
	char *ret;
	int i;
	
	if (exp < 0)
		return alloc_str(0);
	
	ret = malloc(exp + 1);
	i = -1;
	while (++i < exp && i < 52)
		ret[i] = bits[i];
	while (i < exp)
		ret[i++] = '0';
	ret[i] = 0;
	return (ret);
}

char *get_bits_fra(char *bits, int exp)
{
	char *ret;
	int i;
	int j;
	
	if (exp > 52)
		return alloc_str(0);
	ret = malloc(-exp + 54);
	i = exp - 1;
	j = 0;
	while (++i < 0)
		ret[j++] = '0';
	while (i < 53)
		ret[j++] = bits[i++];
	ret[j] = 0;
	return (ret);
}
