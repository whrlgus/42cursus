#include "raycast.h"

void dda(t_ray *ray, char **map, t_pair_double sideDist)
{
	t_pair_double deltaDist;
	t_pair_int step;

	deltaDist = calcDeltaDist(*ray);
	step = calcStep(*ray);
	while (1)
	{
		if(sideDist.x < sideDist.y)
		{
			sideDist.x += deltaDist.x;
			ray->map.x += step.x;
			ray->side = 0;
		}
		else
		{
			sideDist.y += deltaDist.y;
			ray->map.y += step.y;
			ray->side = 1;
		}
		if(map[ray->map.x][ray->map.y] == '1')
			break;
	}
}

double calcPerpWallDist(t_cub *cub, t_ray *ray){
	t_pair_double deltaDist;
	t_pair_double sideDist;
	t_pair_int step;

	deltaDist = calcDeltaDist(*ray);
	sideDist = calcSideDist(*ray, deltaDist,cub->player.pos.x,cub->player.pos.y);
	step = calcStep(*ray);
	dda(ray, cub->map.data, sideDist);
	if(ray->side == 0)
		return ((ray->map.x - cub->player.pos.x + (1 - step.x) / 2) / ray->dir.x);
	else
		return ((ray->map.y - cub->player.pos.y + (1 - step.y) / 2) / ray->dir.y);
}

t_ray initRay(t_player player, int x, int w){
	t_ray ray;
	double camera_x;

	camera_x = 2 * x / (double)w - 1;
	ray.dir.x = player.dir.x + player.plane.x * camera_x;
	ray.dir.y = player.dir.y + player.plane.y * camera_x;
	ray.map.x = (int)player.pos.x;
	ray.map.y = (int)player.pos.y;
	return (ray);
}
