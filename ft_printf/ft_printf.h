#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
#include "/Users/gihyun/github/42cursus/Libft/libft.h"

typedef struct	s_format_info{
	int 		minus;
	int 		plus;
	int 		space;
	int 		zero;
	int 		hash;
	int 		width;
	int 		precision;
	int			length;
	char		type;
}				t_fmt_info;

extern const char	*g_base_10;
extern const char	*g_base_16_l;
extern const char	*g_base_16_u;
extern const char	*g_specifier;
extern t_fmt_info	*g_info;
extern va_list		g_ap;


// read format 함수
int read_specifier(const char **fmt);
int read_flags(const char **fmt);
int read_width(const char **fmt);
int read_precision(const char **fmt);
int read_length(const char **fmt);

// 보조 함수
void append_chars(char **src, char c, long long cnt, int front);
void pad_space_for_i(char **str, size_t *len);
int get_nbr_len(unsigned long long num, int base_len);
char *ft_utoa(unsigned long long num, const char *base);

// 형식 지정자에 따른 printf 함수
size_t print_signed_integer(void);
size_t print_unsigned_integer(void);
size_t print_pointer(void);
size_t print_character(void);
size_t print_string(void);
size_t print_invalid_type(void);
void write_num_of_chars(size_t len);

int ft_printf(const char *, ...);
#endif
