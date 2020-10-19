#include "cub3d.h"

t_rgb init_rgb(char *s)
{
	t_rgb rgb;
	char **token;
	
	token = ft_split(s, ' ');
	rgb.r = ft_atoi(token[0]);
	rgb.r = ft_atoi(token[1]);
	rgb.r = ft_atoi(token[2]);
	free_2d_arr(token, 3);
	return rgb;
}

int parse_key_texture(t_cub *cub, char *key,char *file_path){
	int ret;
	
	if (ft_strcmp(key, "EA"))
		ret = set_texture(&cub->texture[0], file_path);
	else if (ft_strcmp(key, "WE"))
		ret = set_texture(&cub->texture[1], file_path);
	else if (ft_strcmp(key, "SO"))
		ret = set_texture(&cub->texture[2], file_path);
	else if (ft_strcmp(key, "NO"))
		ret = set_texture(&cub->texture[3], file_path);
	else
		ret = set_texture(&cub->texture[4], file_path);
	
	return ret;
}

int parse_key(t_cub *cub, char *s)
{
	char **token;
	int cnt;
	int len;
	
	token = ft_split(s, ' ');
	cnt = count_token(token);
	len = (int)ft_strlen(token[0]);
	if (len == 1 && is_included(token[0][0], "RFC")){
		if (token[0][0] == 'R')
		{
			cub->window.width = ft_atoi(token[1]);
			cub->window.height = ft_atoi(token[2]);
		}
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

int set_cub(t_cub cub, t_string_array *conf) {
	int i;
	
	ft_bzero(&cub, sizeof(cub));
	i = -1;
	while(++i < conf->size && !is_included(conf->ele[i][0]," 01"))
	{
		if (!ft_strlen(conf->ele[i]))
			continue;
		if(!parse_key(&cub, conf->ele[i]))
			return (0);
	}
	cub.map.size = calc_size(conf, i);
	cub.map.data = init_map(conf->ele, i, cub.map.size);
	cub.player = init_player(&cub.map);
	return (1);
}
