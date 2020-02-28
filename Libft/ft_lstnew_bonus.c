#include "libft.h"

t_list *ft_lstnew(void *content)
{
	t_list *ret;
	
	ret = malloc(sizeof(t_list));
	ret->content = content;
	ret->next = 0;
	return (ret);
}
