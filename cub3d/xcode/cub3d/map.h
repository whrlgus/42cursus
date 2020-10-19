#ifndef map_h
#define map_h

#include <stdlib.h>
#include "utility.h"

#define mapWidth 24
#define mapHeight 24


char** initMap(void);
char** init_map(char **strs, int start, t_pair_int size);
t_pair_int calc_size(t_string_array *arr, int i);
#endif /* map_h */
