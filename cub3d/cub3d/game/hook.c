/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 12:43:43 by gicho             #+#    #+#             */
/*   Updated: 2020/10/24 12:43:43 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hook.h"
#include "type.h"

int	exit_hook(int val)
{
	exit(0);
	return (val);
}

int	key_pressed(int key, t_control *control)
{
	if (key == 53)
		exit(0);
	control->keyboard[key] = 1;
	return (0);
}

int	key_released(int key, t_control *control)
{
	control->keyboard[key] = 0;
	return (0);
}

int	motion_notified(int x, int y, t_control *control)
{
	control->new_mouse_point.x = x;
	return (y);
}
