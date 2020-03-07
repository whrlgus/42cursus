#include "ft_printf.h"

const char	*g_base_10;
const char	*g_base_16_l;
const char	*g_base_16_u;
const char	*g_specifier;
t_fmt_info	*g_info;
va_list		g_ap;

// MARK:- format 정보 저장을 위한 함수

int read_specifier(const char **fmt)
{
	const char *ptr;
	
	ptr = g_specifier;
	while (*ptr)
	{
		if (**fmt==*ptr)
		{
			g_info->type = *((*fmt)++);
			return (1);
		}
		++ptr;
	}
	return (0);
}

int read_flags(const char **fmt)
{
	char c;
	
	c = **fmt;
	if (c == '-')
		g_info->minus = 1;
	else if (c == '+')
		g_info->plus = 1;
	else if (c == ' ')
		g_info->space = 1;
	else if (c == '#')
		g_info->hash = 1;
	else if (c == '0')
		g_info->zero = 1;
	else
		return (0);
	++(*fmt);
	return (1);
}

int read_width(const char **fmt)
{
	char c = **fmt;
	if (c == '*'){
		g_info->width = va_arg(g_ap, int);
		++(*fmt);
	}else if(ft_isdigit(c)){ // c=='0'인 조건은 검사하지 않아도 됨
		g_info->width = ft_atoi(*fmt);
		while (ft_isdigit(**fmt))
			++(*fmt);
	}else
		return (0);
	return (1);
}

int read_precision(const char **fmt)
{
	char c;
	
	if(**fmt != '.')
		return (0);
	c = *(++(*fmt));
	g_info->precision = 0;
	if (c == '*'){
		g_info->precision = va_arg(g_ap, int);
		++(*fmt);
	}else if(ft_isdigit(c)){
		g_info->precision = ft_atoi(*fmt);
		while (ft_isdigit(**fmt))
			++(*fmt);
	}
	return (1);
}

int read_length(const char **fmt)
{
	if (**fmt == 'h')
	{
		if (g_info->length < 0 && *(*fmt + 1) && *(*fmt + 1) == 'h')
		{
			g_info->length = 0;
			++(*fmt);
		}
		else if (g_info->length < 1)
			g_info->length = 1;
	}
	else if (**fmt == 'l')
	{
		if (*(*fmt + 1) && *(*fmt + 1) == 'l')
		{
			g_info->length = 3;
			++(*fmt);
		}
		else if (g_info->length < 2)
			g_info->length = 2;
	}
	else
		return (0);
	++(*fmt);
	return (1);
}


// MARK:- 보조 함수

void append_chars(char **src, char c, long long cnt, int front)
{
	char *tmp;
	char *chars;
	
	if (cnt <= 0)
		return ;
	chars = malloc(sizeof(char) * (cnt + 1));
	chars[cnt] = 0;
	ft_memset(chars, c, cnt);
	if (front)
		tmp = ft_strjoin(chars, *src);
	else
		tmp = ft_strjoin(*src, chars);
	free(chars);
	free(*src);
	*src = tmp;
}

void pad_space_for_i(char **str, size_t *len)
{
	long long cnt;
	
	if (g_info->width > (long long)*len)
	{
		cnt = g_info->width - *len;
		append_chars(str, ' ', cnt, !g_info->minus);
		*len += cnt;
	}
}

int get_nbr_len(unsigned long long num, int base_len)
{
	return num ? 1 + get_nbr_len(num / base_len, base_len) : 0;
}

char *ft_utoa(unsigned long long num, const char *base)
{
	int len;
	char *ret;
	int base_len;
	
	base_len = (int)ft_strlen(base);
	len = 1 + get_nbr_len(num / base_len, base_len);
	ret = malloc(sizeof(char) * (len + 1));
	ret[len] = 0;
	while(--len >= 0)
	{
		ret[len] = base[(num % base_len)];
		num /= base_len;
	}
	return (ret);
}

// MARK:- %d %i (signed integer)

long long read_arg_for_si(void)
{
	if (g_info->length == 3)
		return va_arg(g_ap, long long);
	else if (g_info->length == 2)
		return (long)va_arg(g_ap, long);
	else if (g_info->length == 1)
		return (short)va_arg(g_ap, int);
	else if (g_info->length == 0)
		return (char)va_arg(g_ap, int);
	else
		return (int)va_arg(g_ap, int);
}

void pad_zero_for_si(char **str, size_t *len, int neg)
{
	long long cnt;
	
	if (g_info->precision >= 0)
	{
		if (g_info->precision > (long long)*len)
		{
			cnt = g_info->precision - *len;
			append_chars(str, '0', cnt, 1);
			*len += cnt;
		}
	}
	else
	{
		if (!g_info->minus && g_info->zero && g_info->width > (long long)*len)
		{
			cnt = g_info->width - *len;
			if (neg || g_info->plus || g_info->space)
				--cnt;
			append_chars(str, '0', cnt, 1);
			*len += cnt;
		}
	}
}

void add_sign_for_si(char **str, size_t *len, int neg)
{
	char sign;
	
	if (neg || g_info->plus || g_info->space)
	{
		if (neg)
			sign = '-';
		else
			sign = g_info->plus ? '+' : ' ';
		append_chars(str, sign, 1, 1);
		++(*len);
	}
}

size_t print_signed_integer(void)
{
	long long num;
	char *str;
	size_t len;
	int neg;
	
	num = read_arg_for_si();
	neg = (num < 0);
	str = neg ? ft_utoa(-num, g_base_10): ft_utoa(num, g_base_10);
	if (num == 0 && g_info->precision == 0)
		str[0] = 0;
	len = ft_strlen(str);
	pad_zero_for_si(&str, &len, neg);
	add_sign_for_si(&str, &len, neg);
	pad_space_for_i(&str, &len);
	ft_putstr_fd(str, 1);
	free(str);
	return (len);
}

// MARK:- %u %x %X (unsigned integer) %p (pointer)

unsigned long long read_arg_for_usi(void)
{
	if (g_info->length == 3)
		return va_arg(g_ap, unsigned long long);
	else if (g_info->length == 2)
		return (unsigned long)va_arg(g_ap, unsigned long);
	else if (g_info->length == 1)
		return (unsigned short)va_arg(g_ap, unsigned int);
	else if (g_info->length == 0)
		return (unsigned char)va_arg(g_ap, unsigned int);
	else
		return (unsigned int)va_arg(g_ap, unsigned int);
}

void pad_zero_for_usi(char **str, size_t *len)
{
	long long cnt;
	
	if (g_info->precision >= 0)
	{
		if (g_info->precision > (long long)*len)
		{
			cnt = g_info->precision - *len;
			append_chars(str, '0', cnt, 1);
			*len += cnt;
		}
	}
	else if (g_info->zero && g_info->width > (long long)*len)
	{
		cnt = g_info->width - *len;
		if (g_info->type != 'u' && g_info->hash)
			cnt -= 2;
		if (cnt > 0)
		{
			append_chars(str, '0', cnt, 1);
			*len += cnt;
		}
	}
}

void add_prefix_for_usi(char **str, size_t *len)
{
	char c;
	
	if (g_info->hash && (g_info->type == 'x' || g_info->type == 'X'))
	{
		c = (g_info->type == 'x' ? 'x' : 'X');
		append_chars(str, c, 1, 1);
		append_chars(str, '0', 1, 1);
		*len += 2;
	}
}

size_t print_unsigned_integer(void)
{
	unsigned long long num;
	char *str;
	size_t len;
	
	num = read_arg_for_usi();
	if(g_info->type=='u')
		str = ft_utoa(num, g_base_10);
	else if(g_info->type=='x')
		str = ft_utoa(num, g_base_16_l);
	else
		str = ft_utoa(num, g_base_16_u);
	if (num == 0 && g_info->precision == 0)
		str[0] = 0;
	len = ft_strlen(str);
	if (num == 0)
		g_info->hash = 0;
	pad_zero_for_usi(&str, &len);
	add_prefix_for_usi(&str, &len);
	pad_space_for_i(&str, &len);
	ft_putstr_fd(str, 1);
	free(str);
	return (len);
}

size_t print_pointer(void)
{
	char *str;
	size_t len;
	
	g_info->hash = 1;
	g_info->type = 'x';
	str = ft_utoa((long long)va_arg(g_ap, void*), g_base_16_l);
	len = ft_strlen(str);
	pad_zero_for_usi(&str, &len);
	add_prefix_for_usi(&str, &len);
	pad_space_for_i(&str, &len);
	ft_putstr_fd(str, 1);
	free(str);
	return (len);
}

// TODO:- %f %e %g (real number)

typedef struct s_real_num{
	char sign;
	char *exponent;
	char *fraction;
}t_real_num;

t_real_num *rm;

size_t free_rm(t_real_num *rm)
{
	size_t len;
	
	len = 1 + ft_strlen(rm->exponent) + ft_strlen(rm->fraction);
	free(rm->exponent);
	free(rm->fraction);
	return (len);
}

size_t print_real_number(void)
{
//	t_real_num *rn;
//	double num = va_arg(g_ap, double);
	
//	if(g_info->type=='u')
//		str = ft_utoa(num, g_base_10);
//	else if(g_info->type=='x')
//		str = ft_utoa(num, g_base_16_l);
//	else
//		str = ft_utoa(num, g_base_16_u);
//	len = ft_strlen(str);
//	pad_zero_for_usi(&str, &len);
//	add_prefix_for_usi(&str, &len);
//	pad_space_for_i(&str, &len);
//	ft_putstr_fd(str, 1);
	
	
	return 0;//free_rm(rm);
}

// MARK:- %c, %s, invalid type (string)

void pad_for_string(char **str, size_t *len)
{
	long long cnt;
	char c;
	
	if (g_info->width > (long long)*len)
	{
		cnt = g_info->width - *len;
		c = ((g_info->minus || !g_info->zero) ? ' ' : '0');
		append_chars(str, c, cnt, !g_info->minus);
		*len += cnt;
	}
}

size_t print_character(void)
{
	char *str;
	size_t len;

	str = malloc(2);
	str[0] = g_info->length == 2 ? va_arg(g_ap, wint_t) : va_arg(g_ap, int);
	str[1] = 0;
	len = 1;
	pad_for_string(&str, &len);
	ft_putstr_fd(str, 1);
	free(str);
	return (len);
}

size_t print_string(void)
{
	char *str;
	size_t len;
	
	if (g_info->precision != -1)
		str = ft_substr(va_arg(g_ap, char*), 0, g_info->precision);
	else
		str = ft_strjoin(va_arg(g_ap, char*), "");
	len = ft_strlen(str);
	pad_for_string(&str, &len);
	ft_putstr_fd(str, 1);
	free(str);
	return (len);
}

size_t print_invalid_type(void)
{
	char *str;
	size_t len;
	
	str = malloc(sizeof(char) * 2);
	str[0] = g_info->type;
	str[1] = 0;
	len = 1;
	pad_for_string(&str, &len);
	ft_putstr_fd(str, 1);
	free(str);
	return (len);
}

// MARK:- %n (write num of str printed)

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

// MARK:- printf

void init_format_info(void)
{
	g_info->minus = 0;
	g_info->plus = 0;
	g_info->space = 0;
	g_info->hash = 0;
	g_info->zero = 0;
	g_info->width = 0;
	g_info->precision = -1;
	g_info->length = -1;
	g_info->type = 0;
}

size_t print_format_string(void)
{
	char t;
	
	t = g_info->type;
	if (t == 'd' || t == 'i')
		return print_signed_integer();
	else if (t == 'u' || t == 'x' || t == 'X')
		return print_unsigned_integer();
	else if (t == 'f' || t == 'e' || t == 'g')
		return print_real_number();
	else if (t == 'c')
		return print_character();
	else if (t == 's')
		return print_string();
	else if (t == 'p')
		return print_pointer();
	else
		return print_invalid_type();
}

void parse(const char *fmt, size_t *len)
{
	while (*fmt)
		if (*fmt == '%')
		{
			++fmt;
			init_format_info();
			while (read_flags(&fmt) || read_width(&fmt) ||
			read_precision(&fmt) || read_length(&fmt))
				;
			g_info->type = *(fmt++);
			if (g_info->type == 'n')
				write_num_of_chars(*len);
			else if (g_info->type)
				*len += print_format_string();
		}
		else
		{
			ft_putchar_fd(*fmt++, 1);
			++(*len);
		}
}

int ft_printf(const char *fmt, ...)
{
	size_t ret;
	
	ret = 0;
	g_base_10 = "0123456789";
	g_base_16_l = "0123456789abcdef";
	g_base_16_u = "0123456789ABCDEF";
	g_specifier = "cspdiuxX%nfge";
	g_info = malloc(sizeof(t_fmt_info));
	va_start(g_ap, fmt);
	parse(fmt, &ret);
	free(g_info);
	va_end(g_ap);
	return (ret);
}
