#include "utility.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int s1_len;
	int s2_len;
	
	s1_len = (int)ft_strlen(s1);
	s2_len = (int)ft_strlen(s2);
	if (s1_len != s2_len)
		return (s1_len - s2_len);
	return (ft_strncmp(s1, s2, s1_len));
}
