#ifndef fileio_h
#define fileio_h

#include <fcntl.h>
#include "utility.h"
#include "error.h"
#include "get_next_line.h"

int read_file(char *file_path, t_string_array *str_arr);
#endif
