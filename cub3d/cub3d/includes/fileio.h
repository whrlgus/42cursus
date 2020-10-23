#ifndef fileio_h
#define fileio_h

#include <fcntl.h>
#include "utility.h"
#include "error.h"
#include "get_next_line.h"

int read_file(char *file_path, t_string_array *str_arr);
int save_image_to_bmp_file(int** data, int width, int height);
#endif
