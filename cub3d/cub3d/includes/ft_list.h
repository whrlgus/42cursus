/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 01:22:34 by gicho             #+#    #+#             */
/*   Updated: 2020/02/11 20:05:38 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIST_H
# define FT_LIST_H

# include <stdlib.h>

typedef struct		s_list
{
	struct s_list	*next;
	void			*data;
}					t_list;

t_list				*ft_create_elem(void *data);
t_list				*ft_list_at(t_list *begin_list, unsigned int nbr);
void				ft_list_clear(t_list *begin_list, void (*free_fct)(void *));
t_list				*ft_list_find(t_list *begin_list, void *data_ref,
									int (*cmp)());
void				ft_list_foreach(t_list *begin_list, void (*f)());
void				ft_list_push_back(t_list **begin_list, void *data);
void				ft_list_sort(t_list **begin_list, int (*cmp)());
int					ft_list_size(t_list *begin_list);

#endif
