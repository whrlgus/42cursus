/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 12:43:43 by gicho             #+#    #+#             */
/*   Updated: 2020/10/24 12:43:43 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_H
# define UTILITY_H

# include <stdlib.h>
# include "type.h"
# include "libft.h"

int			append(t_string_array *str_arr, char *str);
int			count_token(char **token);
int			is_included(char c, char *set);
int			count_chars(const char *s, int c);
int			is_all_digit(const char *s);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_max(int num1, int num2);
int			ft_min(int num1, int num2);
char		**init_chars_array(int row, int col, char c);
void		free_2d_arr(char **arr, int size);
t_pair_int	next_pos(int i, int j, int d);
t_rgb		init_rgb(char *s);

#endif
