#include "libft.h"

void ft_lstclear(t_list **lst, void (*del)(void*))
{
	if (*lst)
	{
		ft_lstclear(&(*lst)->next, del);
		del((*lst)->content);
		(*lst)->next=0;
		free(*lst);
		*lst = 0;
	}
}
