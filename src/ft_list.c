#include <cub3d.h>

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*buff;

	if (new)
	{
		buff = ft_lstlast(*lst);
		if (!buff)
			*lst = new;
		else
			buff->next = new;
	}
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list	*buff;

	if (lst && new)
	{
		buff = *lst;
		*lst = new;
		new->next = buff;
	}
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next_item;

	if (lst && del)
	{
		while (*lst)
		{
			next_item = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = next_item;
		}
	}
}

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst)
	{
		del(lst->content);
		lst->next = NULL;
		free(lst);
	}
}

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (lst && f)
	{
		while (lst)
		{
			(*f)(lst->content);
			lst = lst->next;
		}
	}
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (0);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

t_list
	*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void *))
{
	t_list	*ret;
	t_list	*new;

	if (!f || !del)
		return (NULL);
	ret = NULL;
	while (lst)
	{
		new = ft_lstnew((*f)(lst->content));
		if (!new)
		{
			ft_lstclear(&ret, del);
			lst = NULL;
			return (NULL);
		}
		ft_lstadd_back(&ret, new);
		lst = lst->next;
	}
	return (ret);
}

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *) malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

int	ft_lstsize(t_list *lst)
{
	unsigned int	len;

	if (lst == NULL)
		return (0);
	len = 1;
	while (lst->next != NULL)
	{
		lst = lst->next;
		len++;
	}
	return (len);
}
