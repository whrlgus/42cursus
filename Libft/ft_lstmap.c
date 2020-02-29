#include "libft.h"

t_list *ft_lstmap(t_list *lst, void *(*f)(void *),void (*del)(void *))
{
	t_list	*ret;
	t_list	*tmp;
	
	ret = 0;
	while (lst)
	{
		if(!(tmp = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(&ret, del);
			return (0);
		}
		
		ft_lstadd_back(&ret, tmp);
		lst = lst->next;
	}
	
	return (ret);
}

//t_list  *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
//{
//	t_list	*newnode;
//	t_list	*newcontent;
//​
//	if (!f || !del)
//		return (NULL);
//	newnode = NULL;
//	while (lst)
//	{
//		if (!(newcontent = ft_lstnew(f(lst->content))))
//		{
//			ft_lstclear(&lst, del);
//			return (NULL);
//		}
//		ft_lstadd_back(&newnode, newcontent);
//		lst = lst->next;
//	}
//	return (newnode);
//}
