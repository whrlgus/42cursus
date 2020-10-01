#include "cub3d.h"
#include <unistd.h>

void *mlx_ptr;
void *win_ptr;

t_player player;
t_point_of_view movement, rotation;

#define min(x,y) x<y?x:y
#define max(x,y) x>y?x:y

int keyboard[300];
t_pair_int old_mouse_point, new_mouse_point;

void set_player_pov(int *pov_component, int key1, int key2)
{
	if(keyboard[key1] && !keyboard[key2]) *pov_component = 1;
	else if(!keyboard[key1] && keyboard[key2]) *pov_component = -1;
	else *pov_component = 0;
}

void calc_movement(){
	int tmp = (old_mouse_point.x - new_mouse_point.x) / 2;
	
	if(tmp){
		rotation.horizontal = tmp;
		old_mouse_point.x = new_mouse_point.x;
	}
	else
		set_player_pov(&rotation.horizontal, key_arrow_left, key_arrow_right);
	
	set_player_pov(&movement.vertical, key_w, key_s);
	set_player_pov(&movement.horizontal, key_d, key_a);
}

int key_pressed(int key){
	keyboard[key] = 1;
	return 0;
}

int key_released(int key){
	keyboard[key] = 0;
	return 0;
}

int motion_notified(int x, int y) {
	new_mouse_point.x = x;
	return 0;
}

int loop(void *param){
	calc_movement();
	update_player(&player, &movement, &rotation);
	redraw(&player);
	usleep(1000);
	return 0;
}



void *img_ptr;
int *data;


int main() {
	player.posX = 22, player.posY = 12;  //x and y start position
	player.dirX = -1, player.dirY = 0; //initial direction vector
	player.planeX = 0, player.planeY = 0.66; //the 2d raycaster version of camera plane

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, mapWidth, mapHeight, "gicho");

	img_ptr = mlx_new_image(mlx_ptr, mapWidth, mapHeight);
	data = (int *)mlx_get_data_addr(img_ptr, &bpp, &sl, &endian);

	mlx_hook(win_ptr, 2, 0, key_pressed, 0);
	mlx_hook(win_ptr, 3, 0, key_released, 0);
	mlx_hook(win_ptr, 6, 0, motion_notified, 0);


	mlx_loop_hook(mlx_ptr, loop, 0);
	mlx_loop(mlx_ptr);
	
	return 0;
}
