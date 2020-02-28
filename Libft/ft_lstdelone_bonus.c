#include "libft.h"

void ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst)
		return ;
	else if (!lst->next)
	{
		del(lst->content);
		free(lst);
	}
	else
	{
		while (lst->next->next)
			lst = lst->next;
		del(lst->next->content);
		free(lst->next);
		lst->next = 0;
	}
}
