#include "sprite.h"

int init_sprite(t_list **head, t_map *map){
	int i;
	int j;
	
	i = -1;
	while (++i < map->size.y)
	{
		j = -1;
		while (++j < map->size.x)
			if (is_included(map->data[i][j], "2"))
			{
				t_sprite *sprite = malloc(sizeof(t_sprite));
				sprite->pos.x = 0.5 + i;
				sprite->pos.y = 0.5 + j;
				sprite->tex_num = 4;
				ft_list_push_back(head, (void*)sprite);
			}
	}
	
	return 1;
}
