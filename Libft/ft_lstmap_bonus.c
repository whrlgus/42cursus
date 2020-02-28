#include "libft.h"

t_list *ft_lstmap(t_list *lst, void *(*f)(void *),void (*del)(void *))
{
	t_list	*ret;
	t_list	*tmp;
	
	ret = 0;
	tmp = lst;
	while (lst)
	{
		ft_lstadd_back(&ret, ft_lstnew(f(lst->content)));
		lst = lst->next;
	}
	ft_lstclear(&tmp, del);
	
	return (ret);
}
