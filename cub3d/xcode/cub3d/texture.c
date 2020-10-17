#include "texture.h"

int** initTexture() {
	char *relative_path[8] = {
		"/Users/gihyun/tmp/images/eagle.xpm",
		"/Users/gihyun/tmp/images/redbrick.xpm",
		"/Users/gihyun/tmp/images/purplestone.xpm",
		"/Users/gihyun/tmp/images/greystone.xpm",
		"/Users/gihyun/tmp/images/bluestone.xpm",
		"/Users/gihyun/tmp/images/mossy.xpm",
		"/Users/gihyun/tmp/images/wood.xpm",
		"/Users/gihyun/tmp/images/colorstone.xpm"
	};
	int **texture = (int **)malloc(8*sizeof(int*));
	int tmp;
	for(int i=0;i<8;++i){
		texture[i] = (int *)malloc(texWidth * texHeight*sizeof(int));
		void *img = mlx_xpm_file_to_image(mlx_init(), relative_path[i], &tmp, &tmp);
		int *data = (int *)mlx_get_data_addr(img, &tmp, &tmp, &tmp);
		texture[i] = data;
	}
	return texture;
}
