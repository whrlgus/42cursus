#include "cub3d.h"

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
	redraw(*mlx);
	usleep(1000);
	return 0;
}

int main() {
	init_game();
	
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
/*
 R 1920 1080
 NO ./path_to_the_north_texture
 SO ./path_to_the_south_texture
 WE ./path_to_the_west_texture
 EA ./path_to_the_east_texture
 
 S ./path_to_the_sprite_texture
 F 220,100,0
 C 225,30,0
 
 map info
 
 inittexture
 initsprite
 initfloor
 initceil
 initmap
 */


//int     main(void)
//{
//	void    *mlx;
//	void    *img;
//	char    *relative_path = "/Users/gihyun/github/42cursus/cub3d/cub3d/cub3d/wood.xpm";
//	int     img_width;
//	int     img_height;
//
//	mlx = mlx_init();
//	win_ptr = mlx_new_window(mlx, screenWidth, screenHeight, "gicho");
//	img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
//	data = (int *)mlx_get_data_addr(img, &bpp, &sl, &endian);
//	mlx_put_image_to_window(mlx, win_ptr, img, 0, 0);
//
//	mlx_loop(mlx);
//	return 0;
//}
