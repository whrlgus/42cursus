/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 13:09:10 by gicho             #+#    #+#             */
/*   Updated: 2020/10/24 13:09:10 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOK_H
# define HOOK_H

# include <stdlib.h>
# include "type.h"

int exit_hook(int val);
int key_pressed(int key, t_control *control);
int key_released(int key, t_control *control);
int motion_notified(int x, int y, t_control *control);

#endif
