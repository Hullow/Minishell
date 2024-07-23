t_list	*ft_fill_list(char ***split, int *dimensions, int i, int j)
{
	t_list	*node;
	t_list	*head;

	node = NULL;
	head = NULL;
	while (++i < dimensions[0])
	{
		while (++j < dimensions[1])
		{
			if (node)
			{
				node->next = ft_lstnew(ft_fill_pt(split[i], i, j, dimensions));
				node = node->next;
			}
			else
			{
				node = ft_lstnew(ft_fill_pt(split[i], i, j, dimensions));
				head = node;
			}
		}
		j = -1;
	}
	ft_free_array(split, dimensions);
	ft_free((void **)&dimensions);
	return (head);
}