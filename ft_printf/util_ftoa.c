#include "normalize.h"

char *next(char *str, int num)
{
	char *ret;
	int i;
	int carry;
	int tmp;
	
	ret = malloc(ft_strlen(str) + 2);
	i = 0;
	carry = 0;
	while (str[i])
	{
		tmp = (str[i] - '0') * num + carry;
		ret[i] = (tmp % 10) + '0';
		carry = tmp / 10;
		++i;
	}
	free(str);
	ret[i++] = carry + '0';
	ret[i] = 0;
	return (ret);
}

int max(int a, int b)
{
	return a < b ? b : a;
}
char *init(char c)
{
	char *ret;
	
	ret = malloc(2);
	ret[0] = c;
	ret[1] = 0;
	return (ret);
}

void swap(char **a, char **b)
{
	char *tmp;
	
	tmp = *a;
	*a = *b;
	*b = tmp;
}

char *add(char *a, char *b)
{
	char *ret;
	int i;
	int carry;
	int tmp;
	
	ret = malloc(ft_strlen(a) + 2);
	i = 0;
	carry = 0;
	while(b[i])
	{
		tmp = (a[i] - '0' + b[i] - '0' + carry);
		ret[i++] = (tmp % 10) + '0';
		carry = tmp / 10;
	}
	while(a[i])
	{
		tmp = (a[i] - '0' + carry);
		ret[i++] = (tmp % 10) + '0';
		carry = tmp / 10;
	}
	if (carry)
		ret[i++] = carry + '0';
	ret[i] = 0;
	return (ret);
}
