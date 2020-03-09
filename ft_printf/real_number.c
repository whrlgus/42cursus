#include "ft_printf.h"





size_t print_real_number(void)
{
	char *str;
	double num;
	
	num = va_arg(g_ap, double);
	str = ft_ftoa(num);
	

	
	free(str);
	return 0;
}


