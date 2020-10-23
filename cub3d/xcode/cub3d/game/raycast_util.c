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
	return (sideDist);
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
	return (step);
}

t_pair_double calcDeltaDist(t_ray ray){
	t_pair_double deltaDist;

	deltaDist.x = fabs(1 / ray.dir.x);
	deltaDist.y = fabs(1 / ray.dir.y);
	return (deltaDist);
}
