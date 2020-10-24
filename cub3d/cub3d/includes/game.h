/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 12:43:43 by gicho             #+#    #+#             */
/*   Updated: 2020/10/24 12:43:43 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "player.h"
# include "map.h"
# include "window.h"
# include "texture.h"
# include "control.h"
# include "error.h"
# include "fileio.h"
# include "validation.h"
# include "sprite.h"

extern t_cub	g_cub;
int				init_game(char *cub_file_path);
int				set_cub(t_cub *cub, t_string_array *conf);

#endif
