#ifndef texture_h
#define texture_h

#include <stdlib.h>
#include <mlx.h>
#include "type.h"

#define texWidth 64
#define texHeight 64

int** initTexture(void);
int set_texture(t_texture *texture, char *file_path);
#endif /* texture_h */
