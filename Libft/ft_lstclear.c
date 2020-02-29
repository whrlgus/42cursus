#include "libft.h"

void ft_lstclear(t_list **lst, void (*del)(void*))
{
	if (*lst)
	{
		ft_lstclear(&(*lst)->next, del);
		ft_lstdelone(*lst, del);
		(*lst)->next=0;
		*lst = 0;
	}
}
