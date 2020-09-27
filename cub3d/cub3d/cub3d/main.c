#include "cub3d.h"
#include <unistd.h>

void *mlx_ptr;
void *win_ptr;

void key_pressed(int key){
	printf("%d\n",key);
	if(key == key_arrow_up || key == key_arrow_down)
		move_key = key;
	if(key == key_arrow_left || key == key_arrow_right)
		rotate_key = key;
}

void key_released(int key){
	if(key == key_arrow_up || key == key_arrow_down)
		move_key = -1;
	if(key == key_arrow_left || key == key_arrow_right)
		rotate_key = -1;
}

int loop(void *param){
	
	move_position();
	draw();
	
	return 0;
}

void *img_ptr;
int *data;

int main() {
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, mapWidth, mapHeight, "gicho");
	
	img_ptr = mlx_new_image(mlx_ptr, mapWidth, mapHeight);
	data = (int *)mlx_get_data_addr(img_ptr, &bpp, &sl, &endian);
	
	mlx_hook(win_ptr, 2, 0, key_pressed, 0);
	mlx_hook(win_ptr, 3, 0, key_released, 0);
//
	mlx_loop_hook(mlx_ptr, loop, 0);
	mlx_loop(mlx_ptr);
	
	return 0;
}
