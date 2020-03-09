#include "ft_ftoa.h"

static char *ftoa_int(char *bits)
{
	char *ret;
	char *num;
	char *tmp;
	int i;
	
	ret = init('0');
	num = init('1');
	i = (int)ft_strlen(bits);
	while(--i >= 0)
	{
		if (bits[i] == '1')
		{
			if(ft_strlen(ret) > ft_strlen(num))
				tmp = add(ret, num);
			else
				tmp = add(num, ret);
			free(ret);
			ret = tmp;
		}
		num = next(num, 2);
	}
	return (ret);
}

static char *ftoa_fra(char *bits)
{
	char *ret;
	char *num;
	char *tmp;
	
	ret = init('0');
	num = init('5');
	while(*bits)
	{
		if (*bits == '1')
		{
			tmp = (ft_strlen(ret) > ft_strlen(num) ? add(ret, num) : add(num, ret));
			free(ret);
			ret = tmp;
		}
		if (*(++bits))
		{
			ret = next(ret, 10);
			num = next(num, 5);
		}
		else
			break;
	}
	return (ret);
}


typedef struct s_real_num
{
	int exp;
	char *bits;
}	t_real_num;

t_real_num *g_rm;

void init_g_rm(long long *num)
{
	int i;

	g_rm = malloc(sizeof(t_real_num));
	g_rm->bits = malloc(54);
	g_rm->bits[0] = '1';
	g_rm->bits[53] = 0;
	i = 63;
	g_rm->exp=0;
	while (--i >= 52)
		g_rm->exp = (g_rm->exp<<1) + 1&(*num>>i);
	g_rm->exp-=((1<<10)-2);
	++i;
	while (--i >= 0)
		g_rm->bits[52 - i] = (1&(*num>>i) ? '1' : '0');
}

char *make_str_int(void)
{
	char *ret;
	char *tmp;
	int i;
	
	if (g_rm->exp < 0)
	{
		ret = malloc(2);
		ret[0] = '0';
		ret[1] = 0;
	}
	else
	{
		tmp = malloc(g_rm->exp + 1);
		i = -1;
		while (++i < g_rm->exp && i < 52)
			tmp[i] = g_rm->bits[i];
		while (i < g_rm->exp)
			tmp[i++] = '0';
		tmp[i] = 0;
		ret = ftoa_int(tmp);
		free(tmp);
	}
	return (ret);
}

char *make_str_fra(void)
{
	char *ret;
	char *tmp;
	int i;
	int j;
	
	if (g_rm->exp > 52)
	{
		ret = malloc(2);
		ret[0] = '0';
		ret[1] = 0;
	}
	else
	{
		tmp = malloc(-g_rm->exp + 54);
		i = g_rm->exp;
		j = 0;
		while (i < 0)
			tmp[j++] = '0';
		while (i < 53)
			tmp[j++] = g_rm->bits[i++];
		tmp[j] = 0;
		ret = ftoa_fra(tmp);
		free(tmp);
	}
	return (ret);
}

void str_rev(char *str)
{
	char *ptr;
	char tmp;
	
	ptr = str + ft_strlen(str) - 1;
	while (str < ptr)
	{
		tmp = *ptr;
		*ptr = *str;
		*str = tmp;
		++str;
		--ptr;
	}
}

char *ft_ftoa(double num)
{
	char *ret;
	char *str_int;
	char *str_fra;
	char *tmp;
	
	init_g_rm(&num);
	str_int = make_str_int();
	str_fra = make_str_fra();
	str_rev(str_int);
	str_rev(str_fra);
	tmp = ft_strjoin(str_int, ".");
	ret = ft_strjoin(tmp, str_fra);
	free(str_int);
	free(str_fra);
	free(tmp);
	free(g_rm->bits);
	free(g_rm);
	return (ret);
}
