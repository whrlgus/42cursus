#include "cub3d.h"
#include<math.h>
int worldMap[mapWidth][mapHeight]=
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
int bpp;
int sl;
int endian;



double tim = 0; //time of current frame
double oldTime = 0; //time of previous frame

int stop=0;

#include <unistd.h>

typedef struct s_ray{
	t_pair_int map;
	t_pair_double dir;
	int side;
}t_ray;

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

double calcPerpWallDist(t_ray *ray, double posX, double posY){
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
		if(worldMap[ray->map.x][ray->map.y] > 0) break;
	}
	if(ray->side == 0)
		return (ray->map.x - posX + (1 - step.x) / 2) / ray->dir.x;
	else
		return (ray->map.y - posY + (1 - step.y) / 2) / ray->dir.y;
}

t_ray initRay(t_player *player, int x, int w){
	t_ray ray;
	double cameraX = 2 * x / (double)w - 1;
	
	ray.dir.x = player->dirX + player->planeX * cameraX;
	ray.dir.y = player->dirY + player->planeY * cameraX;
	ray.map.x = (int)player->posX;
	ray.map.y = (int)player->posY;
	
	return ray;
}

void updateImage(){
	
}

void redraw(t_player *player){
	int w=mapWidth,h=mapHeight;
	memset(data,0,h*w*4);
	for(int x = 0; x < w; x++)
	{
		t_ray ray=initRay(player, x, w);
		double perpWallDist = calcPerpWallDist(&ray,player->posX,player->posY);
		int lineHeight = (int)(h / perpWallDist);
		int drawStart = lineHeight > h ? 0 : (h - lineHeight) / 2;
		int drawEnd = lineHeight >= h ? h - 1 : (lineHeight + h) / 2;
		
		int color;
		switch(worldMap[ray.map.x][ray.map.y])
		{
			case 1:  color = 0xff0000; break; //red
			case 2:  color = 0x00ff00; break; //green
			case 3:  color = 0x0000ff; break; //blue
			case 4:  color = 0xffffff; break; //white
			default: color = 0x0f0f0f; break; //yellow
		}
		
		if(ray.side == 1)color /= 2;
		for(int i=drawStart;i<drawEnd;++i)data[i*sl/4+x]=color;
	}
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
}
