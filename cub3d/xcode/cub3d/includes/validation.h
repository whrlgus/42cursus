//
//  validation.h
//  cub3d
//
//  Created by 조기현 on 2020/10/19.
//

#ifndef validation_h
#define validation_h

#include "utility.h"
#include "map.h"

int is_valid_conf(t_string_array *conf);
int is_valid_key(char* str, int chk[]);
int is_valid_map(t_string_array *conf, int *i, int chk[]);
#endif /* validation_h */
