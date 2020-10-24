/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_pos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 12:43:43 by gicho             #+#    #+#             */
/*   Updated: 2020/10/24 12:43:43 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utility.h"

t_pair_int	next_pos(int i, int j, int d)
{
	static int	di[] = {0, 0, 1, -1};
	static int	dj[] = {1, -1, 0, 0};
	t_pair_int	ret;

	ret.y = i + di[d];
	ret.x = j + dj[d];
	return (ret);
}
