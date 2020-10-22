#include "player.h"

t_pair_double	calc_dir(t_player *p)
{
	t_pair_double dir;
	
	dir.x = p->dir.x;
	dir.y = p->dir.y;
	if (p->movement.horizontal && p->movement.vertical)
	{
		dir.x = (p->movement.vertical * p->dir.x
				 + p->movement.horizontal * p->dir.y) / sqrt(2);
		dir.y = (p->movement.vertical * p->dir.y
				 - p->movement.horizontal * p->dir.x) / sqrt(2);
	}
	else if (p->movement.horizontal)
	{
		dir.x = p->movement.horizontal * p->dir.y;
		dir.y = -p->movement.horizontal * p->dir.x;
	}
	else if (p->movement.vertical)
	{
		dir.x *= p->movement.vertical;
		dir.y *= p->movement.vertical;
	}
	
	return (dir);
}

void	update_position(char **map, t_player *p, t_pair_double dir)
{
	double moveSpeed;
	double nPosX;
	double nPosY;
	
	moveSpeed = 0.05;
	nPosX = p->pos.x + dir.x * moveSpeed;
	nPosY = p->pos.y + dir.y * moveSpeed;
	
//
//	double rad=0.2;
//	for(int i=0;i<360;++i){
//		int x = rad * cos((double)i * M_PI / 180);
//		int y = rad * sin((double)i * M_PI / 180);
//		if(map[y])
//
//	}
	
	if(map[(int)nPosX][(int)(p->pos.y)] == '0') p->pos.x = nPosX;
	if(map[(int)p->pos.x][(int)nPosY] == '0') p->pos.y = nPosY;
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
