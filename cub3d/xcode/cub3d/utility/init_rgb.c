#include "utility.h"

t_rgb init_rgb(char *s)
{
	t_rgb rgb;
	char **token;
	
	token = ft_split(s, ',');
	rgb.r = ft_atoi(token[0]);
	rgb.g = ft_atoi(token[1]);
	rgb.b = ft_atoi(token[2]);
	free_2d_arr(token, 3);
	return rgb;
}
