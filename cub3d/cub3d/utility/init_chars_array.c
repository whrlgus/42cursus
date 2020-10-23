#include "utility.h"

char** init_chars_array(int row, int col, char c)
{
	char** ret;
	int i;
	
	ret = (char**)malloc(sizeof(char*) * row);
	i = 0;
	while (i < row)
	{
		ret[i] = (char*)malloc(sizeof(char) * col);
		ft_memset(ret[i], c, col);
		++i;
	}
	
	return (ret);
}
