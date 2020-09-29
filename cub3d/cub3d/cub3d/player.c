#include "cub3d.h"

t_pair_double	calc_dir(t_player *player,
						 t_point_of_view *movement)
{
	t_pair_double dir;
	
	dir.x = player->dirX;
	dir.y = player->dirY;
	if (movement->horizontal && movement->vertical)
	{
		dir.x = (movement->vertical * player->dirX
				+ movement->horizontal * player->dirY) / sqrt(2);
		dir.y = (movement->vertical * player->dirY
				- movement->horizontal * player->dirX) / sqrt(2);
	}
	else if (movement->horizontal)
	{
		dir.x = movement->horizontal * player->dirY;
		dir.y = -movement->horizontal * player->dirX;
	}
	else if (movement->vertical)
	{
		dir.x *= movement->vertical;
		dir.y *= movement->vertical;
	}
	
	return (dir);
}

void	update_position(t_player *player,
						t_pair_double dir)
{
	double moveSpeed = 0.05;
	double nPosX = player->posX + dir.x * moveSpeed;
	double nPosY = player->posY + dir.y * moveSpeed;
	if(worldMap[(int)nPosX][(int)player->posY] == 0) player->posX = nPosX;
	if(worldMap[(int)player->posX][(int)nPosY] == 0) player->posY = nPosY;
}


void	update_direction(t_player *player,t_point_of_view *rotation)
{
	
	double rotSpeed = 0.02 * rotation->horizontal;
	double oldDirX = player->dirX;
	player->dirX = player->dirX * cos(rotSpeed) - player->dirY * sin(rotSpeed);
	player->dirY = oldDirX * sin(rotSpeed) + player->dirY * cos(rotSpeed);
	double oldPlaneX = player->planeX;
	player->planeX = player->planeX * cos(rotSpeed) - player->planeY * sin(rotSpeed);
	player->planeY = oldPlaneX * sin(rotSpeed) + player->planeY * cos(rotSpeed);
}

void	update_player(t_player *player,
					  t_point_of_view *movement,
					  t_point_of_view *rotation)
{
	t_pair_double old_dir;
	t_pair_double old_plane;
	
	old_dir.x = player->dirX;
	old_dir.y = player->dirY;
	old_plane.x = player->planeX;
	old_plane.y = player->planeY;
	
	if(movement->horizontal || movement->vertical)
		update_position(player, calc_dir(player, movement));
	if(rotation->horizontal || rotation->vertical)
		update_direction(player, rotation);
}





