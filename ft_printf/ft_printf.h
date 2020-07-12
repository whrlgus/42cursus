/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 22:30:14 by gicho             #+#    #+#             */
/*   Updated: 2020/07/11 22:30:14 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "Libft/libft.h"

typedef struct		s_format_info{
	int 			minus;
	int 			plus;
	int 			space;
	int 			zero;
	int 			hash;
	int 			width;
	int 			precision;
	int				length;
	char			type;
}					t_fmt_info;

typedef struct		s_normalized_real_num
{
	int				neg;
	int				exp;
	char			*str;
}					t_nrm;

typedef struct		s_real_num
{
	int				exp;
	char			*bits;
}					t_real_num;

extern const char	*g_base_10;
extern const char	*g_base_16_l;
extern const char	*g_base_16_u;
extern const char	*g_specifier;
extern t_fmt_info	*g_info;
extern va_list		g_ap;
extern t_nrm		*g_nrm;

int					read_specifier(const char **fmt);
int					read_flags(const char **fmt);
int					read_width(const char **fmt);
int					read_precision(const char **fmt);
int					read_length(const char **fmt);
void				append_chars(char **src, char c, long long cnt, int front);
void				pad_space_for_i(char **str, size_t *len);
int					get_nbr_len(unsigned long long num, int base_len);
char				*utoa(unsigned long long num, const char *base);
size_t				print_signed_integer(void);
size_t				print_unsigned_integer(void);
size_t				print_pointer(void);
size_t				print_character(void);
size_t				print_string(void);
size_t				print_invalid_type(void);
size_t				print_real_number(void);
void				write_num_of_chars(size_t len);
void				ft_ftoa(double num, char **str_int, char **str_fra);
int					ft_printf(const char *, ...);
int					get_exp(long long *num);
char				*get_frac_bits(long long *num);
char				*get_bits_int(char *bits, int exp);
char				*get_bits_fra(char *bits, int exp);
char				*next(char *str, int num);
char				*alloc_str(char c);
char				*add(char *a, char *b);
void				str_rev(char *str);
void				trim_right(char *str);
void				round_num(char **str, int i);
void				append_suffix(char **str);
void				insert_decimal_point(void);
void				pad_zero(void);
void				pad_space(void);

#endif
