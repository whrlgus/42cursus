/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 12:43:43 by gicho             #+#    #+#             */
/*   Updated: 2020/10/24 12:43:43 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		calc_pov(int key1, int key2, t_control *control)
{
	int pov;

	if (control->keyboard[key1] && !control->keyboard[key2])
		pov = 1;
	else if (!control->keyboard[key1] && control->keyboard[key2])
		pov = -1;
	else
		pov = 0;
	return (pov);
}

void	calc_movement(t_player *p, t_control *control)
{
	int tmp;

	tmp = (control->old_mouse_point.x - control->new_mouse_point.x) / 3;
	if (tmp)
	{
		p->rotation.horizontal = tmp;
		control->old_mouse_point.x = control->new_mouse_point.x;
	}
	else
		p->rotation.horizontal = calc_pov(key_arrow_left,
											key_arrow_right, control);
	p->movement.vertical = calc_pov(key_w, key_s, control);
	p->movement.horizontal = calc_pov(key_d, key_a, control);
}
