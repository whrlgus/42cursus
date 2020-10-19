#include "cub3d.h"
#include <fcntl.h>
#include <stdio.h>
void redraw(t_mlx mlx){
	for(int i=0;i<g_cub.window.height;++i)
		for(int j=0;j<g_cub.window.width;++j)
			mlx.data[i*mlx.sl/4+j]=g_cub.window.scene[i][j];
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, mlx.img_ptr, 0, 0);
}

int loop(t_mlx *mlx){
	calc_movement(&g_cub.player, &g_control);
	update_player(g_cub.map.data, &g_cub.player);
	update_scene(g_cub.map.data, g_cub.window, g_cub.player);
	
//	printf("%f %f\n",g_player.plane.x,g_player.plane.y);
	redraw(*mlx);
	usleep(1000);
	return 0;
}

t_cub g_cub;

int main(int argc, const char* argv[]) {
	
	char *file_path = "/Users/gihyun/tmp/1.cub";
	t_string_array conf;
	if(read_file(file_path, &conf) == -1)
		return -1;
	if(!is_valid_conf(&conf))
		return print_error(cuberror(invalid_config_format));
	
	if(!set_cub(&g_cub, &conf)) return -1;
	
	t_mlx mlx;
	
	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, g_cub.window.width, g_cub.window.height, "gicho");
	mlx.img_ptr = mlx_new_image(mlx.mlx_ptr, g_cub.window.width, g_cub.window.height);
	mlx.data = (int *)mlx_get_data_addr(mlx.img_ptr, &mlx.bpp, &mlx.sl, &mlx.endian);

	mlx_hook(mlx.win_ptr, 2, 0, key_pressed, &g_control);
	mlx_hook(mlx.win_ptr, 3, 0, key_released, &g_control);
	mlx_hook(mlx.win_ptr, 6, 0, motion_notified, &g_control);
	mlx_loop_hook(mlx.mlx_ptr, loop, &mlx);
	mlx_loop(mlx.mlx_ptr);

	return 0;
}
