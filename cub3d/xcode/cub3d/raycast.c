#include "raycast.h"

t_pair_double calcSideDist(t_ray ray,
						   t_pair_double deltaDist, double posX, double posY) {
	t_pair_double sideDist;
	
	if(ray.dir.x < 0)
		sideDist.x = (posX - ray.map.x) * deltaDist.x;
	else
		sideDist.x = (ray.map.x + 1.0 - posX) * deltaDist.x;
	if(ray.dir.y < 0)
		sideDist.y = (posY - ray.map.y) * deltaDist.y;
	else
		sideDist.y = (ray.map.y + 1.0 - posY) * deltaDist.y;
	
	return sideDist;
}

t_pair_int calcStep(t_ray ray) {
	t_pair_int step;
	
	if(ray.dir.x < 0)
		step.x = -1;
	else
		step.x = 1;
	if(ray.dir.y < 0)
		step.y = -1;
	else
		step.y = 1;
	
	return step;
}
t_pair_double calcDeltaDist(t_ray ray){
	t_pair_double deltaDist;
	
	deltaDist.x = fabs(1 / ray.dir.x);
	deltaDist.y = fabs(1 / ray.dir.y);
	
	return deltaDist;
}

double calcPerpWallDist(char **map, t_ray *ray, double posX, double posY){
	t_pair_double deltaDist = calcDeltaDist(*ray);
	t_pair_double sideDist = calcSideDist(*ray, deltaDist,posX,posY);
	t_pair_int step = calcStep(*ray);
	
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
		if(map[ray->map.x][ray->map.y] == '1') break;
	}
	if(ray->side == 0)
		return (ray->map.x - posX + (1 - step.x) / 2) / ray->dir.x;
	else
		return (ray->map.y - posY + (1 - step.y) / 2) / ray->dir.y;
}

t_ray initRay(t_player player, int x, int w){
	t_ray ray;
	double cameraX = 2 * x / (double)w - 1;
	
	ray.dir.x = player.dir.x + player.plane.x * cameraX;
	ray.dir.y = player.dir.y + player.plane.y * cameraX;
	ray.map.x = (int)player.pos.x;
	ray.map.y = (int)player.pos.y;
	
	return ray;
}
