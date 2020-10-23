#ifndef map_h
#define map_h

#include <stdlib.h>
#include "utility.h"

char** init_map(char **strs, int start, t_pair_int size);
t_pair_int calc_size(t_string_array *arr, int i);
#endif 
