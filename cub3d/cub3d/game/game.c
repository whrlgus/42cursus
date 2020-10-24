/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 12:43:43 by gicho             #+#    #+#             */
/*   Updated: 2020/10/24 12:43:43 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

t_cub g_cub;

int		parse_key_texture(t_cub *cub, char *key, char *file_path)
{
	int ret;

	if (ft_strcmp(key, "EA") == 0)
		ret = load_texture(&cub->texture[0], file_path);
	else if (ft_strcmp(key, "WE") == 0)
		ret = load_texture(&cub->texture[1], file_path);
	else if (ft_strcmp(key, "SO") == 0)
		ret = load_texture(&cub->texture[2], file_path);
	else if (ft_strcmp(key, "NO") == 0)
		ret = load_texture(&cub->texture[3], file_path);
	else
		ret = load_texture(&cub->texture[4], file_path);
	if (!ret)
		print_error(cuberror(invlid_texture_file));
	return (ret);
}

int		parse_key(t_cub *cub, char *s)
{
	char	**token;
	int		cnt;
	int		len;

	token = ft_split(s, ' ');
	cnt = count_token(token);
	len = (int)ft_strlen(token[0]);
	if (len == 1 && is_included(token[0][0], "RFC"))
	{
		if (token[0][0] == 'R')
			cub->window = init_window(ft_atoi(token[1]), ft_atoi(token[2]));
		else if (token[0][0] == 'F')
			cub->floor = init_rgb(token[1]);
		else
			cub->ceil = init_rgb(token[1]);
	}
	else if (!parse_key_texture(cub, token[0], token[1]))
		return (0);
	free_2d_arr(token, cnt);
	return (1);
}

int		set_cub(t_cub *cub, t_string_array *conf)
{
	int i;

	ft_bzero(cub, sizeof(t_cub));
	i = -1;
	while (++i < conf->size && !is_included(conf->ele[i][0], " 01"))
	{
		if (!ft_strlen(conf->ele[i]))
			continue;
		if (!parse_key(cub, conf->ele[i]))
			return (0);
	}
	cub->map.size = calc_size(conf, i);
	cub->map.data = init_map(conf->ele, i, cub->map.size);
	cub->player = init_player(&cub->map);
	init_sprite(&cub->sprite, &cub->map);
	cub->zbuf = malloc(sizeof(double) * cub->window.width);
	return (1);
}

int		init_game(char *cub_file_path)
{
	int				ret;
	t_string_array	conf;

	ft_bzero(&conf, sizeof(conf));
	ret = 1;
	if (read_file(cub_file_path, &conf) == -1)
		ret = 0;
	else if (!is_valid_conf(&conf))
	{
		print_error(cuberror(invalid_config_format));
		ret = 0;
	}
	else if (!set_cub(&g_cub, &conf))
		ret = 0;
	free_2d_arr(conf.ele, conf.size);
	return (ret);
}
