#include "cub3d.h"
#include <fcntl.h>
#include <stdio.h>
void redraw(t_mlx mlx){
	for(int i=0;i<g_window.height;++i)
		for(int j=0;j<g_window.width;++j)
			mlx.data[i*mlx.sl/4+j]=g_window.scene[i][j];
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, mlx.img_ptr, 0, 0);
}

int loop(t_mlx *mlx){
	calc_movement(&g_player, &g_control);
	update_player(g_map, &g_player);
	update_scene(g_map, g_window, g_player);
	
	printf("%f %f\n",g_player.plane.x,g_player.plane.y);
	redraw(*mlx);
	usleep(1000);
	return 0;
}



int main(int argc, const char* argv[]) {
	
	char *file_path = "/Users/gihyun/tmp/1.cub";
	t_string_array conf;
	if(read_file(file_path, &conf) == -1)
		return -1;
	if(!is_valid_conf(&conf))
		return print_error(cuberror(invalid_config_format));
	
	
	
	
	init_game();
	texture=initTexture();
	
	t_mlx mlx;
	
	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, g_window.width, g_window.height, "gicho");
	mlx.img_ptr = mlx_new_image(mlx.mlx_ptr, g_window.width, g_window.height);
	mlx.data = (int *)mlx_get_data_addr(mlx.img_ptr, &mlx.bpp, &mlx.sl, &mlx.endian);

	mlx_hook(mlx.win_ptr, 2, 0, key_pressed, &g_control);
	mlx_hook(mlx.win_ptr, 3, 0, key_released, &g_control);
	mlx_hook(mlx.win_ptr, 6, 0, motion_notified, &g_control);
	mlx_loop_hook(mlx.mlx_ptr, loop, &mlx);
	mlx_loop(mlx.mlx_ptr);

	return 0;
}
