#include "window.h"

t_window init_window(int width, int height){
	t_window window;
	
	window.width = width;
	window.height = height;
	
	window.scene = (int**)malloc(height*sizeof(int*));
	for(int i=0;i<height;++i)window.scene[i]=(int*)malloc(width*sizeof(int));
	
	return window;
}

void set_background(t_window *window, t_rgb floor, t_rgb ceil) {
	int w=window->width,h=window->height;
	for(int x = 0; x < w; x++)
	{
		for(int y = 0; y < h/2 ; y++)
		window->scene[y][x] = (floor.r << 16) + (floor.g << 8) + floor.b;
		for(int y = h/2; y < h ; y++)
		window->scene[y][x] = (ceil.r << 16) + (ceil.g << 8) + ceil.b;
	}
}

void set_wall(t_window *window, t_map map, t_texture texture[], t_player player) {
	
	int w=window->width,h=window->height;
	
	for(int x = 0; x < w; x++)
	{
		t_ray ray=initRay(player, x, w);
		double perpWallDist = calcPerpWallDist(map.data,&ray,player.pos.x,player.pos.y);
		g_cub.zbuf[x]=perpWallDist;
		int lineHeight = (int)(h / perpWallDist);
		int drawStart = lineHeight > h ? 0 : (h - lineHeight) / 2;
		int drawEnd = lineHeight >= h ? h - 1 : (lineHeight + h) / 2;
		
		int texNum = map.data[ray.map.x][ray.map.y] - 1;
		
		texNum = 0;
		if(ray.side) {
			texNum = ray.dir.y > 0 ? 0 : 1;
		} else {
			texNum = ray.dir.x > 0 ? 2 : 3;
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
			
			int color = texture[texNum].data[texHeight * texY + texX];
			
			window->scene[y][x]=color;
			
		}
	}
}

int pow2(int val){
	return val * val;
}
int compare(t_sprite *lhs, t_sprite *rhs){
	int lhs_dist = pow2(lhs->pos.x - g_cub.player.pos.x) + pow2(lhs->pos.y - g_cub.player.pos.y);
	int rhs_dist = pow2(rhs->pos.x - g_cub.player.pos.x) + pow2(rhs->pos.y - g_cub.player.pos.y);
	return lhs_dist < rhs_dist;
}

void foo(t_sprite *sprite) {
	int w=g_cub.window.width, h=g_cub.window.height;
	double spriteX = sprite->pos.x - g_cub.player.pos.x;
	double spriteY = sprite->pos.y - g_cub.player.pos.y;
	double invDet = 1.0 / (g_cub.player.plane.x * g_cub.player.dir.y -
						   g_cub.player.dir.x * g_cub.player.plane.y); //required for correct matrix multiplication
	
	double transformX = invDet * (g_cub.player.dir.y * spriteX - g_cub.player.dir.x * spriteY);
	double transformY = invDet * (-g_cub.player.plane.y * spriteX + g_cub.player.plane.x * spriteY); //this is actually the depth inside the screen, that what Z is in 3D
	
	int spriteScreenX = (int)((w / 2) * (1 + transformX / transformY));
	
	//calculate height of the sprite on screen
	int spriteHeight = abs((int)(h / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
	//calculate lowest and highest pixel to fill in current stripe
	int drawStartY = -spriteHeight / 2 + h / 2;
	if(drawStartY < 0) drawStartY = 0;
	int drawEndY = spriteHeight / 2 + h / 2;
	if(drawEndY >= h) drawEndY = h - 1;
	
	//calculate width of the sprite
	int spriteWidth = abs( (int) (h / (transformY)));
	int drawStartX = -spriteWidth / 2 + spriteScreenX;
	if(drawStartX < 0) drawStartX = 0;
	int drawEndX = spriteWidth / 2 + spriteScreenX;
	if(drawEndX >= w) drawEndX = w - 1;
	
	//loop through every vertical stripe of the sprite on screen
	for(int stripe = drawStartX; stripe < drawEndX; stripe++)
	{
		int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256;
		//the conditions in the if are:
		//1) it's in front of camera plane so you don't see things behind you
		//2) it's on the screen (left)
		//3) it's on the screen (right)
		//4) ZBuffer, with perpendicular distance
		if(stripe > 0 && stripe < w && transformY > 0 && transformY < g_cub.zbuf[stripe])
			for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
		{
			int d = (y) * 256 - h * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
			int texY = ((d * texHeight) / spriteHeight) / 256;
			unsigned int color = g_cub.texture[sprite->tex_num].data[texWidth * texY + texX]; //get current color from the texture
			if((color & 0x00FFFFFF) != 0) g_cub.window.scene[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
		}
	}
}

void set_sprite(t_cub *cub) {
	ft_list_sort(&cub->sprite, compare);
	ft_list_foreach(cub->sprite, foo);
}

void update_scene(){
	set_background(&g_cub.window, g_cub.floor, g_cub.ceil);
	set_wall(&g_cub.window, g_cub.map, g_cub.texture, g_cub.player);
	set_sprite(&g_cub);
}
