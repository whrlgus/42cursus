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

double posX = 22, posY = 12;  //x and y start position
double dirX = -1, dirY = 0; //initial direction vector
double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

double tim = 0; //time of current frame
double oldTime = 0; //time of previous frame

int stop=0;

#include <unistd.h>

void draw9(){
	int w=mapWidth,h=mapHeight;
	memset(data,0,h*w*4);
	for(int x = 0; x < w; x++)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double)w - 1; //x-coordinate in camera space
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;
		//which box of the map we're in
		int mapX = (int)posX;
		int mapY = (int)posY;
		
		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;
		
		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;
		
		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;
		
		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if(rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}
		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if(sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if(worldMap[mapX][mapY] > 0) hit = 1;
		}
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if(side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
		else          perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;
		
		//Calculate height of line to draw on screen
		int lineHeight = (int)(h / perpWallDist);
		
		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + h / 2;
		if(drawStart < 0)drawStart = 0;
		int drawEnd = lineHeight / 2 + h / 2;
		if(drawEnd >= h)drawEnd = h - 1;
		
		//choose wall color
		int color;
		switch(worldMap[mapX][mapY])
		{
			case 1:  color = 0xff0000;    break; //red
			case 2:  color = 0x00ff00;  break; //green
			case 3:  color = 0x0000ff;   break; //blue
			case 4:  color = 0xffffff;  break; //white
			default: color = 0x0f0f0f; break; //yellow
		}
		
		//give x and y sides different brightness
		if(side == 1) {color = color / 2;}
		
		//draw the pixels of the stripe as a vertical line
		
		for(int i=drawStart;i<drawEnd;++i)data[i*sl/4+x]=color;
	}
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
	
	
}



void redraw1(){
	void *img_ptr = mlx_new_image(mlx_ptr, mapWidth, mapHeight);
	int *data = (int *)mlx_get_data_addr(img_ptr, &bpp, &sl, &endian);
	for(int i=200;i<400;++i)for(int j=200;j<400;++j)
		data[i*sl/4+j]=0x00ff00;
	
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
}

void redraw2(){
	
	void *img_ptr = mlx_new_image(mlx_ptr, 800, 600);
	int *data = (int *)mlx_get_data_addr(img_ptr, &bpp, &sl, &endian);
	for(int i=400;i<600;++i)for(int j=400;j<600;++j)
		data[i*832+j]=0x00ff00;
	//		mlx_pixel_put(mlx_ptr, win_ptr, i, j, 0xff0000);
	
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
	
	
}


typedef struct s_pair_double{
	double x,y;
}t_pair_double;

typedef struct s_pair_int{
	int x,y;
}t_pair_int;

typedef struct s_ray{
	t_pair_int map;
	t_pair_double dir;
	int side;
}t_ray;

t_pair_double calcSideDist(t_ray ray, t_pair_double deltaDist) {
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

double calcPerpWallDist(t_ray *ray){
	t_pair_double deltaDist = calcDeltaDist(*ray);
	t_pair_double sideDist = calcSideDist(*ray, deltaDist);
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

t_ray initRay(int x, int w){
	t_ray ray;
	double cameraX = 2 * x / (double)w - 1;
	ray.dir.x = dirX + planeX * cameraX;
	ray.dir.y = dirY + planeY * cameraX;
	ray.map.x = (int)posX;
	ray.map.y = (int)posY;
	return ray;
}

void draw(){
	int w=mapWidth,h=mapHeight;
	memset(data,0,h*w*4);
	for(int x = 0; x < w; x++)
	{
		t_ray ray=initRay(x, w);
		double perpWallDist = calcPerpWallDist(&ray);
		int lineHeight = (int)(h / perpWallDist);
		int drawStart = lineHeight > h ? 0 : (h - lineHeight) / 2;
		int drawEnd = lineHeight >= h ? h - 1 : (lineHeight + h) / 2;
		
		int color;
		switch(worldMap[ray.map.x][ray.map.y])
		{
			case 1:  color = 0xff0000;    break; //red
			case 2:  color = 0x00ff00;  break; //green
			case 3:  color = 0x0000ff;   break; //blue
			case 4:  color = 0xffffff;  break; //white
			default: color = 0x0f0f0f; break; //yellow
		}
		
		if(ray.side == 1)color /= 2;
		for(int i=drawStart;i<drawEnd;++i)data[i*sl/4+x]=color;
	}
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
}
