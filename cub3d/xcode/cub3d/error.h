//
//  error.h
//  cub3d
//
//  Created by 조기현 on 2020/10/19.
//

#ifndef error_h
#define error_h

#include "libft.h"
#include <string.h>
#include <errno.h>

enum e_error{
	invalid_file_name,
	gnl_error,
	invalid_config_format
};

char* cuberror(enum e_error type);
int print_error(char *msg);
#endif /* error_h */
