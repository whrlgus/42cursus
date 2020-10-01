#include "player.h"

t_pair_double	calc_dir(t_player *player,
						 t_point_of_view *movement)
{
	t_pair_double dir;
	
	dir.x = player->dir.x;
	dir.y = player->dir.y;
	if (movement->horizontal && movement->vertical)
	{
		dir.x = (movement->vertical * player->dir.x
				+ movement->horizontal * player->dir.y) / sqrt(2);
		dir.y = (movement->vertical * player->dir.y
				- movement->horizontal * player->dir.x) / sqrt(2);
	}
	else if (movement->horizontal)
	{
		dir.x = movement->horizontal * player->dir.y;
		dir.y = -movement->horizontal * player->dir.x;
	}
	else if (movement->vertical)
	{
		dir.x *= movement->vertical;
		dir.y *= movement->vertical;
	}
	
	return (dir);
}

void	update_position(int **worldMap,
						t_player *player,
						t_pair_double dir)
{
	double moveSpeed = 0.05;
	double nPosX = player->pos.x + dir.x * moveSpeed;
	double nPosY = player->pos.y + dir.y * moveSpeed;
	if(worldMap[(int)nPosX][(int)player->pos.y] == 0) player->pos.x = nPosX;
	if(worldMap[(int)player->pos.x][(int)nPosY] == 0) player->pos.y = nPosY;
}


void	update_direction(t_player *player,t_point_of_view *rotation)
{
	
	double rotSpeed = 0.02 * rotation->horizontal;
	double oldDirX = player->dir.x;
	player->dir.x = player->dir.x * cos(rotSpeed) - player->dir.y * sin(rotSpeed);
	player->dir.y = oldDirX * sin(rotSpeed) + player->dir.y * cos(rotSpeed);
	double oldPlaneX = player->plane.x;
	player->plane.x = player->plane.x * cos(rotSpeed) - player->plane.y * sin(rotSpeed);
	player->plane.y = oldPlaneX * sin(rotSpeed) + player->plane.y * cos(rotSpeed);
}

void	update_player(int **worldMap,
					  t_player *player,
					  t_point_of_view *movement,
					  t_point_of_view *rotation)
{
	t_pair_double old_dir;
	t_pair_double old_plane;
	
	old_dir.x = player->dir.x;
	old_dir.y = player->dir.y;
	old_plane.x = player->plane.x;
	old_plane.y = player->plane.y;
	
	if(movement->horizontal || movement->vertical)
		update_position(worldMap, player, calc_dir(player, movement));
	if(rotation->horizontal || rotation->vertical)
		update_direction(player, rotation);
}
