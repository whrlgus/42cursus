#ifndef raycast_h
#define raycast_h

#include "type.h"
#include <math.h>

t_pair_double calcSideDist(t_ray ray, t_pair_double deltaDist, double posX, double posY);
t_pair_int calcStep(t_ray ray);
t_pair_double calcDeltaDist(t_ray ray);
double calcPerpWallDist(char **map, t_ray *ray, double posX, double posY);
t_ray initRay(t_player player, int x, int w);


#endif /* raycast_h */
