#include "libft.h"

int ft_lstsize(t_list *lst)
{
	int ret;
	
	ret = 0;
	while (lst)
	{
		lst = lst->next;
		++ret;
	}
	return (ret);
}

