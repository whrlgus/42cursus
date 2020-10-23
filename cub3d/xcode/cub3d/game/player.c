#include "player.h"


void	update_position(char **map, t_player *p, t_pair_double dir)
{
	double moveSpeed;
	double nPosX;
	double nPosY;

	moveSpeed = 0.05;
	nPosX = p->pos.x + dir.x * moveSpeed;
	nPosY = p->pos.y + dir.y * moveSpeed;
	
	t_pair_double ndir;
	ndir.x = nPosX;
	ndir.y=p->pos.y;
	update_position_sub(map, p, ndir);
	ndir.x = p->pos.x;
	ndir.y=nPosY;
	update_position_sub(map, p, ndir);
	
}

void	update_direction(t_player *p)
{
	double rotSpeed;
	double oldDirX;
	double oldPlaneX;
	
	rotSpeed = 0.02 * p->rotation.horizontal;
	oldDirX = p->dir.x;
	p->dir.x = p->dir.x * cos(rotSpeed) - p->dir.y * sin(rotSpeed);
	p->dir.y = oldDirX * sin(rotSpeed) + p->dir.y * cos(rotSpeed);
	oldPlaneX = p->plane.x;
	p->plane.x = p->plane.x * cos(rotSpeed) - p->plane.y * sin(rotSpeed);
	p->plane.y = oldPlaneX * sin(rotSpeed) + p->plane.y * cos(rotSpeed);
}

void	update_player(char **map, t_player *p)
{
	t_pair_double old_dir;
	t_pair_double old_plane;
	
	old_dir.x = p->dir.x;
	old_dir.y = p->dir.y;
	old_plane.x = p->plane.x;
	old_plane.y = p->plane.y;
	
	if(p->movement.horizontal || p->movement.vertical)
		update_position(map, p, calc_dir(p));
	if(p->rotation.horizontal || p->rotation.vertical)
		update_direction(p);
}

void set_player(t_player *p, int x, int y, char dir){
	p->pos.x = 0.5 + y;
	p->pos.y = 0.5 + x;
	if(dir == 'E')
	{
		p->dir.y = 1;
		p->plane.x = 0.66;
	}
	else if(dir == 'W')
	{
		p->dir.y = -1;
		p->plane.x = -0.66;
	}
	else if(dir == 'S')
	{
		p->dir.x = 1;
		p->plane.y = -0.66;
	}
	else
	{
		p->dir.x = -1;
		p->plane.y = 0.66;
	}
}

t_player init_player(t_map *map) {
	t_player p;
	int i;
	int j;
	
	ft_bzero(&p, sizeof(p));
	i = -1;
	while (++i < map->size.y)
	{
		j = -1;
		while (++j < map->size.x)
			if (is_included(map->data[i][j], "EWSN"))
			{
				set_player(&p,j,i,map->data[i][j]);
				map->data[i][j] = '0';
				return p;
			}
	}
	return p;
}
