/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 21:48:14 by gicho             #+#    #+#             */
/*   Updated: 2020/07/13 21:48:14 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "Libft/libft.h"

typedef struct		s_format_info{
	int 			minus;
	int 			zero;
	int 			width;
	int 			precision;
	char			type;
}					t_fmt_info;

extern char			*g_specifier;
extern char			*g_base_10;
extern char			*g_base_16_l;
extern char			*g_base_16_u;
extern va_list		g_ap;
extern t_fmt_info	*g_fmt_info;

int					read_flags(const char **fmt);
int					read_width(const char **fmt);
int					read_precision(const char **fmt);

void				set_conv_c(char **str, char c);
void				set_conv_s(char **str);
void				set_conv_uxX(char **str, char *base);
void				set_conv_p(char **str);
void				set_conv_di(char **str);


char*				string(char c, int cnt);
char				*utoa(long long num, const char *base);
void				pad_with_leading_zeros(char **str, int cnt);
char*				ft_strjoin_with_dealloc(char *a, char *b);

#endif
