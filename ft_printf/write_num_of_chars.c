#include "ft_printf.h"

void write_num_of_chars(size_t len)
{
	if (g_info->length == 3)
		*va_arg(g_ap, long long*) = len;
	else if (g_info->length == 2)
		*va_arg(g_ap, long*) = len;
	else if (g_info->length == 1)
		*va_arg(g_ap, short*) = len;
	else if (g_info->length == 0)
		*va_arg(g_ap, char*) = len;
	else
		*va_arg(g_ap, int*) = (int)len;
}