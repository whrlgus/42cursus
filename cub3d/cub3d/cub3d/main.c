#include "cub3d.h"
#include <unistd.h>

void *mlx_ptr;
void *win_ptr;

t_player player;
t_point_of_view movement, rotation;

#define min(x,y) x<y?x:y
#define max(x,y) x>y?x:y

int keyboard[300];

void calc_movement(){
	if(keyboard[key_w] && !keyboard[key_s]) movement.vertical = 1;
	else if(!keyboard[key_w] && keyboard[key_s]) movement.vertical = -1;
	else movement.vertical = 0;
	
	if(keyboard[key_d] && !keyboard[key_a]) movement.horizontal = 1;
	else if(!keyboard[key_d] && keyboard[key_a]) movement.horizontal = -1;
	else movement.horizontal = 0;
	
	if(keyboard[key_arrow_left] && !keyboard[key_arrow_right])
		rotation.horizontal = 1;
	else if(!keyboard[key_arrow_left] && keyboard[key_arrow_right])
		rotation.horizontal = -1;
	else rotation.horizontal = 0;
}

void key_pressed(int key){
	printf("%d\n",key);
	keyboard[key] = 1;
	calc_movement();
}

void key_released(int key){
	keyboard[key] = 0;
	calc_movement();
}

int loop(void *param){
	
	update_player(&player, &movement, &rotation);
	
	redraw(&player);
	usleep(1000);
	
	return 0;
}

void motion_detected(int button, int x, int y) {
	printf("%d %d %d\n",button, x, y);
}

void *img_ptr;
int *data;

int main() {
	player.posX = 22, player.posY = 12;  //x and y start position
	player.dirX = -1, player.dirY = 0; //initial direction vector
	player.planeX = 0, player.planeY = 0.66; //the 2d raycaster version of camera plane
	
	move_key = -1;
	rotate_key = -1;
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, mapWidth, mapHeight, "gicho");

	img_ptr = mlx_new_image(mlx_ptr, mapWidth, mapHeight);
	data = (int *)mlx_get_data_addr(img_ptr, &bpp, &sl, &endian);

	mlx_hook(win_ptr, 2, 0, key_pressed, 0);
	mlx_hook(win_ptr, 3, 0, key_released, 0);
//	mlx_hook(win_ptr, 6, 0, motion_detected, 0);
//	mlx_mouse_hook(win_ptr, motion_detected,0);

	mlx_loop_hook(mlx_ptr, loop, 0);
	mlx_loop(mlx_ptr);
	
	return 0;
}
