#include "cub3d.h"

void redraw(t_mlx mlx){
	for(int i=0;i<g_cub.window.height;++i)
		for(int j=0;j<g_cub.window.width;++j)
			mlx.data[i*g_cub.window.width+j]=g_cub.window.scene[i][j];
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, mlx.img_ptr, 0, 0);
}

int loop(t_mlx *mlx){
	calc_movement(&g_cub.player, &g_cub.control);
	update_player(g_cub.map.data, &g_cub.player);
	update_scene(g_cub.map.data, g_cub.window, g_cub.player);
	
	redraw(*mlx);
//	usleep(1000);
	return 0;
}



int main(int argc, const char* argv[]) {
	char *file_path = "/Users/gihyun/tmp/1.cub";
	if(!init_game(file_path)) return -1;
	
	t_mlx mlx;
	
	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, g_cub.window.width, g_cub.window.height, "gicho");
	mlx.img_ptr = mlx_new_image(mlx.mlx_ptr, g_cub.window.width, g_cub.window.height);
	mlx.data = (int *)mlx_get_data_addr(mlx.img_ptr, &mlx.bpp, &mlx.sl, &mlx.endian);

	mlx_hook(mlx.win_ptr, 2, 0, key_pressed, &g_cub.control);
	mlx_hook(mlx.win_ptr, 3, 0, key_released, &g_cub.control);
	mlx_hook(mlx.win_ptr, 6, 0, motion_notified, &g_cub.control);
	mlx_loop_hook(mlx.mlx_ptr, loop, &mlx);
	mlx_loop(mlx.mlx_ptr);

	return 0;
}
