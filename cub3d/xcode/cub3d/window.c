#include "window.h"

int **texture;

t_window init_window(int width, int height){
	t_window window;
	
	window.width = width;
	window.height = height;
	
	window.scene = (int**)malloc(height*sizeof(int*));
	for(int i=0;i<height;++i)window.scene[i]=(int*)malloc(width*sizeof(int));
	
	return window;
}

void update_scene(char **map, t_window g_window, t_player player){
	int w=g_window.width,h=g_window.height;
	for(int x = 0; x < w; x++)
	{
		for(int y = 0; y < h; y++)g_window.scene[y][x]=0;
		t_ray ray=initRay(player, x, w);
		double perpWallDist = calcPerpWallDist(map,&ray,player.pos.x,player.pos.y);
		int lineHeight = (int)(h / perpWallDist);
		int drawStart = lineHeight > h ? 0 : (h - lineHeight) / 2;
		int drawEnd = lineHeight >= h ? h - 1 : (lineHeight + h) / 2;
		
		int texNum = map[ray.map.x][ray.map.y] - 1;
		
		texNum = 0;
		if(ray.side) {
			texNum = ray.dir.y > 0 ? 2 : 3;
		} else {
			texNum = ray.dir.x > 0 ? 0 : 1;
		}
		
		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if (ray.side == 0) wallX = player.pos.y + perpWallDist * ray.dir.y;
		else           wallX = player.pos.x + perpWallDist * ray.dir.x;
		wallX -= floor((wallX));
		
		//x coordinate on the texture
		int texX = (int)(wallX * (double)texWidth);
		if(ray.side == 0 && ray.dir.x > 0) texX = texWidth - texX - 1;
		if(ray.side == 1 && ray.dir.y < 0) texX = texWidth - texX - 1;
		
		// How much to increase the texture coordinate per screen pixel
		double step = 1.0 * texHeight / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - h / 2 + lineHeight / 2) * step;
		for(int y = drawStart; y<drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY = (int)texPos & (texHeight - 1);
			texPos += step;
			int color = texture[texNum][texHeight * texY + texX];
			
			g_window.scene[y][x]=color;
			
		}
	}
	
}
