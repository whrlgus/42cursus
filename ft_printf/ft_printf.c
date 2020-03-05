#include "ft_printf.h"
t_format *g_format;

const char *g_base_10 = "0123456789";
const char *g_base_16_l = "0123456789abcdef";
const char *g_base_16_u = "0123456789ABCDEF";

// MARK:- check 함수

int check_specifier(const char **fmt)
{
	const char * const specifier="cspdiuxX%nfge";
	char *ptr;
	
	ptr = (char*)specifier;
	while (*ptr)
	{
		if (**fmt==*ptr)
		{
			g_format->type = *((*fmt)++);
			return (1);
		}
		++ptr;
	}
	return (0);
}

int check_flags(const char **fmt)
{
	char c;
	
	c = **fmt;
	if (c == '-')
		g_format->minus = 1;
	else if (c == '+')
		g_format->plus = 1;
	else if (c == ' ')
		g_format->space = 1;
	else if (c == '#')
		g_format->hash = 1;
	else if (c == '0')
		g_format->zero = 1;
	else
		return (0);
	++(*fmt);
	return (1);
}

int check_width(const char **fmt, va_list ap)
{
	char c = **fmt;
	if (c == '*'){
		g_format->width = va_arg(ap, int);
		++(*fmt);
	}else if(ft_isdigit(c)){ // c=='0'인 조건은 검사하지 않아도 됨
		g_format->width = ft_atoi(*fmt);
		while (ft_isdigit(**fmt))
			++(*fmt);
	}else
		return (0);
	return (1);
}

int check_precision(const char **fmt, va_list ap)
{
	char c;
	
	if(**fmt != '.')
		return (0);
	c = *(++(*fmt));
	g_format->precision = 0;
	if (c == '*'){
		g_format->precision = va_arg(ap, int);
		++(*fmt);
	}else if(ft_isdigit(c)){
		g_format->precision = ft_atoi(*fmt);
		while (ft_isdigit(**fmt))
			++(*fmt);
	}
	return (1);
}

int check_length(const char **fmt)
{
	if (**fmt == 'h')
	{
		if (g_format->length < 0 && *(*fmt + 1) && *(*fmt + 1) == 'h')
		{
			g_format->length = 0;
			++(*fmt);
		}
		else if (g_format->length < 1)
			g_format->length = 1;
	}
	else if (**fmt == 'l')
	{
		if (*(*fmt + 1) && *(*fmt + 1) == 'l')
		{
			g_format->length = 3;
			++(*fmt);
		}
		else if (g_format->length < 2)
			g_format->length = 2;
	}
	else
		return (0);
	++(*fmt);
	return (1);
}

int check_format(const char **fmt, va_list ap)
{
	while (check_flags(fmt) || check_width(fmt, ap) ||
	check_precision(fmt, ap) || check_length(fmt))
		;
	g_format->type = (*(*fmt)++);
	if(!g_format->type)
		return (0);
	convert(ap);
	return (1);
}

// MARK:- 보조 함수

char *append_chars(char *src, char c, long long cnt, int front)
{
	char *ret;
	char *chars;
	
	if (cnt <= 0)
		return src;
	chars = malloc(sizeof(char) * (cnt + 1));
	chars[cnt] = 0;
	ft_memset(chars, c, cnt);
	if (front)
		ret = ft_strjoin(chars, src);
	else
		ret = ft_strjoin(src, chars);
	free(chars);
	free(src);
	return (ret);
}

int get_nbr_len(unsigned long long num, int base_len)
{
	return num ? 1 + get_nbr_len(num / base_len, base_len) : 0;
}

char *ft_itoa_pos(unsigned long long num, const char *base)
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

long long read_signed_integer(va_list ap)
{
	if (g_format->length == 3)
		return va_arg(ap, long long);
	else if (g_format->length == 2)
		return (long)va_arg(ap, long);
	else if (g_format->length == 1)
		return (short)va_arg(ap, int);
	else if (g_format->length == 0)
		return (char)va_arg(ap, int);
	else
		return (int)va_arg(ap, int);
}

unsigned long long read_unsigned_integer(va_list ap)
{
	if (g_format->length == 3)
		return va_arg(ap, unsigned long long);
	else if (g_format->length == 2)
		return (unsigned long)va_arg(ap, unsigned long);
	else if (g_format->length == 1)
		return (unsigned short)va_arg(ap, unsigned int);
	else if (g_format->length == 0)
		return (unsigned char)va_arg(ap, unsigned int);
	else
		return (unsigned int)va_arg(ap, unsigned int);
}

void init_format()
{
	g_format->minus = 0;
	g_format->plus = 0;
	g_format->space = 0;
	g_format->hash = 0;
	g_format->zero = 0;
	g_format->width = 0;
	g_format->precision = -1;
	g_format->length = -1;
	g_format->type = 0;
}

// MARK:- convert 함수

// MARK: integer 공통 함수

void pad_space_for_i(char **str, size_t *len)
{
	long long cnt;
	
	if (g_format->width > *len)
	{
		cnt = g_format->width - *len;
		*str = append_chars(*str, ' ', cnt, !g_format->minus);
		*len += cnt;
	}
}

// MARK: signed integer 함수
void pad_zero_for_si(char **str, size_t *len, int neg)
{
	long long cnt;
	
	if (g_format->precision >= 0)
	{
		if (g_format->precision > *len)
		{
			cnt = g_format->precision - *len;
			*str = append_chars(*str, '0', cnt, 1);
			*len += cnt;
		}
	}
	else
	{
		if (!g_format->minus && g_format->zero && g_format->width > *len)
		{
			cnt = g_format->width - *len;
			if (neg || g_format->plus || g_format->space)
				--cnt;
			*str = append_chars(*str, '0', cnt, 1);
			*len += cnt;
		}
	}
}

void add_sign_for_si(char **str, size_t *len, int neg)
{
	char sign;
	
	if (neg || g_format->plus || g_format->space)
	{
		if (neg)
			sign = '-';
		else
			sign = g_format->plus ? '+' : ' ';
		*str = append_chars(*str, sign, 1, 1);
		++(*len);
	}
}

void print_integer_signed(va_list ap)
{
	long long num;
	char *str;
	size_t len;
	int neg;
	
	num = read_signed_integer(ap);
	neg = (num < 0);
	str = neg ? ft_itoa_pos(-num, g_base_10): ft_itoa_pos(num, g_base_10);
	len = ft_strlen(str);
	pad_zero_for_si(&str, &len, neg);
	add_sign_for_si(&str, &len, neg);
	pad_space_for_i(&str, &len);
	ft_putstr_fd(str, 1);
	free(str);
}

// MARK: unsigned integer 함수

void pad_zero_for_usi(char **str, size_t *len)
{
	long long cnt;
	
	if (g_format->precision >= 0)
	{
		if (g_format->precision > *len)
		{
			cnt = g_format->precision - *len;
			*str = append_chars(*str, '0', cnt, 1);
			*len += cnt;
		}
	}
	else if (g_format->zero && g_format->width > *len)
	{
		cnt = g_format->width - *len;
		if (g_format->type != 'u' && g_format->hash)
			cnt -= 2;
		if (cnt > 0)
		{
			*str = append_chars(*str, '0', cnt, 1);
			*len += cnt;
		}
	}
}

void add_prefix_for_usi(char **str, size_t *len)
{
	char c;
	
	if (g_format->hash && (g_format->type == 'x' || g_format->type == 'X'))
	{
		c = (g_format->type == 'x' ? 'x' : 'X');
		*str = append_chars(*str, c, 1, 1);
		*str = append_chars(*str, '0', 1, 1);
		len += 2;
	}
}

void print_integer_unsigned(va_list ap)
{
	unsigned long long num;
	char *str;
	size_t len;
	
	num = read_signed_integer(ap);
	if(g_format->type=='u')
		str = ft_itoa_pos(num, g_base_10);
	else if(g_format->type=='x')
		str = ft_itoa_pos(num, g_base_16_l);
	else
		str = ft_itoa_pos(num, g_base_16_u);
	pad_zero_for_usi(&str, &len);
	add_prefix_for_usi(&str, &len);
	pad_space_for_i(&str, &len);
	ft_putstr_fd(str, 1);
	free(str);
}

// MARK: real number 함수

void print_real_num(va_list ap)
{
	
}

// MARK: %c 함수

void print_char(va_list ap)
{
	ft_putchar_fd(va_arg(ap, int), 1);
}

// MARK: %s 함수

void print_string(va_list ap)
{
	
}

// MARK: %n 함수

void write_num_of_chars(va_list ap)
{
	
}

void convert_nothing()
{
	size_t cnt;
	char *str = malloc(sizeof(char) * 2);
	str[0] = g_format->type;
	str[1] = 0;
	
	if (1 < g_format->width)
	{
		cnt = g_format->width - 1;
		if (g_format->minus)
			str = append_chars(str, ' ', cnt, 0);
		else if (g_format->zero)
			str = append_chars(str, '0', cnt, 1);
		else
			str = append_chars(str, ' ', cnt, 1);
	}
	ft_putstr_fd(str, 1);
	free(str);
}



void convert(va_list ap)
{
	char t;
	
	t = g_format->type;
	if (t == 'd' || t == 'i')
		print_integer_signed(ap);
	else if (t == 'u' || t == 'x' || t == 'X')
		print_integer_unsigned(ap);
	else if (t == 'f' || t == 'e' || t == 'g')
		print_real_num(ap);
	else if (t == 'c')
		print_char(ap);
	else if (t == 's')
		print_string(ap);
	else if (t == 'n')
		write_num_of_chars(ap);
	else
		convert_nothing();
}

// MARK:-

int ft_printf(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	g_format = malloc(sizeof(t_format));
	while (*fmt)
	{
		if (*fmt == '%')
		{
			++fmt;
			init_format();
			check_format(&fmt, ap);
		}
		else
			ft_putchar_fd(*fmt++, 1);
	}
	free(g_format);
	va_end(ap);
	return 0;
}
