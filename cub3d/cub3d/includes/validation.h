/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 13:09:10 by gicho             #+#    #+#             */
/*   Updated: 2020/10/24 13:09:10 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATION_H
# define VALIDATION_H

# include "utility.h"
# include "map.h"

int is_valid_conf(t_string_array *conf);
int is_valid_key(char *str, int chk[]);
int is_valid_map(t_string_array *conf, int *i, int chk[]);

#endif
