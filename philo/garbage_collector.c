#include "../philo.h"


void	*ft_memset(void *b, int c, int len)
{
	int				i;
	unsigned char	value;
	unsigned char	*ptr;

	i = 0;
	value = (unsigned char)c;
	ptr = (unsigned char *)b;
	while (i < len)
	{
		ptr[i] = value;
		i++;
	}
	return (b);
}


void	ft_free(t_allocs **lst)
{
	t_allocs	*l;
	t_allocs	*current;

	if (!lst || !(*lst))
		return ;
	l = *lst;
	while (l)
	{
		current = l->next;
		free((l)->ptr);
		free(l);
		l = current;
	}
	*lst = NULL;
}

void	*ft_malloc(size_t size, int flag)
{
	static t_allocs	*allocations = NULL;
	t_allocs		*new;

	if (!flag)
		return (ft_free(&allocations), NULL);
	new = malloc(sizeof(t_allocs));
	new->ptr = malloc(size);
	if (!(new->ptr))
		return (NULL);
	ft_memset(new->ptr, 0, size);
	new->next = allocations;
	allocations = new;
	return (new->ptr);
}

// void	*ft_calloc(int count, int size)
// {
// 	int		len;
// 	void	*ptr;

// 	len = count * size;
// 	ptr = (void *)ft_malloc(len, 1);
// 	if (!ptr)
// 		return (NULL);
// 	ft_memset(ptr, 0, len);
// 	return (ptr);
// }