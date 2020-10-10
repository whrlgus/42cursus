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

void	update_position(int **worldMap, t_player *p, t_pair_double dir)
{
	double moveSpeed;
	double nPosX;
	double nPosY;
	
	moveSpeed = 0.05;
	nPosX = p->pos.x + dir.x * moveSpeed;
	nPosY = p->pos.y + dir.y * moveSpeed;
	if(worldMap[(int)nPosX][(int)p->pos.y] == 0) p->pos.x = nPosX;
	if(worldMap[(int)p->pos.x][(int)nPosY] == 0) p->pos.y = nPosY;
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

void	update_player(int **map, t_player *p)
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

t_player initPlayer(void) {
	t_player p;
	
	p.pos.x = 22;
	p.pos.y = 12;  //x and y start position
	p.dir.x = -1;
	p.dir.y = 0; //initial direction vector
	p.plane.x = 0;
	p.plane.y = 0.66; //the 2d raycaster version of camera plane
	
	return p;
}
