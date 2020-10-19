#include "texture.h"

int** initTexture() {
	char *relative_path[8] = {
		"/Users/gihyun/tmp/images/south.xpm",
		"/Users/gihyun/tmp/images/north.xpm",
		"/Users/gihyun/tmp/images/east.xpm",
		"/Users/gihyun/tmp/images/west.xpm",
//		"/Users/gihyun/tmp/images/redbrick.xpm",
//		"/Users/gihyun/tmp/images/wood.xpm",
//		"/Users/gihyun/tmp/images/bluestone.xpm",
		"/Users/gihyun/tmp/images/purplestone.xpm",
		"/Users/gihyun/tmp/images/greystone.xpm",
		"/Users/gihyun/tmp/images/mossy.xpm",
		"/Users/gihyun/tmp/images/colorstone.xpm"
	};
	int **texture = (int **)malloc(8*sizeof(int*));
	int tmp;
	for(int i=0;i<8;++i){
		void *img = mlx_xpm_file_to_image(mlx_init(), relative_path[i], &tmp, &tmp);
		texture[i] = (int *)mlx_get_data_addr(img, &tmp, &tmp, &tmp);
	}
	return texture;
}

int set_texture(t_texture *texture, char *file_path)
{
	int tmp;
	
	void *img = mlx_xpm_file_to_image(mlx_init(),
									  file_path,
									  &texture->size.x,
									  &texture->size.y);
	texture->data = (int *)mlx_get_data_addr(img, &tmp, &tmp, &tmp);
	return (texture->data != 0);
}
