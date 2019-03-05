/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 15:31:49 by osamoile          #+#    #+#             */
/*   Updated: 2018/08/24 15:31:50 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

t_list_of_nodes	*create_list_of_nodes(t_node *first_node)
{
	t_list_of_nodes *list = ft_memalloc(sizeof(t_list_of_nodes));
	list->node = first_node;
	list->next = NULL;
	return (list);
}

void	push_node(t_list_of_nodes **list, t_node *node, t_lem *lem)
{
	if (*list == NULL)
		*list = create_list_of_nodes(node);
	else
	{
		t_list_of_nodes *start = *list;

		while ((*list)->next != NULL)
			*list = (*list)->next;
	
		(*list)->next = ft_memalloc(sizeof(t_list_of_nodes));
		(*list)->next->node = node;
		(*list)->next->next = NULL;
		*list = start;
	}
}

t_node	*pop_node(t_list_of_nodes **list)
{
	if (*list == NULL)
		return (NULL);
	t_node *res = (*list)->node;
	t_list_of_nodes *erase = *list;
	*list = (*list)->next;
	free(erase);
	erase = NULL;
	return (res);
}

void	remove_node(t_list_of_nodes **list, t_node *node)
{
	t_list_of_nodes *tmp;
	
	if ((*list)->node == node)
	{
		tmp = *list;
		*list = (*list)->next;
	}
	else
	{
		t_list_of_nodes *start = *list;
		while ((*list)->next)
		{
			if ((*list)->next->node == node)
			{
				tmp = (*list)->next;
				(*list)->next = (*list)->next->next;
				break;
			}
			*list = (*list)->next;
		}
		*list = start;
	}
	free(tmp);
}

t_node	*create_node(char *line, t_lem *lem)
{
	char *itoa1;
	char *itoa2;
	char **params = ft_strsplit(line, ' ');

	if (ft_arrlen(params) != 3 || ft_char_count(' ', line) != 2)
		error("Room definition example: 'name x y'", lem);
	if (params[0][0] == 'L')
		error("Room's name must not start with the character 'L'", lem);
	if (params[0][0] == '#')
		error("Room's name must not start with the character '#'", lem);
	if (ft_char_count('-', params[0]) != 0)
		error("Room's name must not contain the character '-'", lem);
	

	t_node	*node = ft_memalloc(sizeof(t_node));
	node->name = ft_strdup(params[0]);
	node->bfs_used = 0;
	node->bfs_in_queue = 0;
	node->marked = 0;
	node->bfs_prev = NULL;
	itoa1 = ft_itoa(ft_atoi(params[1]));
	itoa2 = ft_itoa(ft_atoi(params[2]));
	if (ft_strequ(itoa1, params[1]) && ft_strequ(itoa2, params[2]))
	{
		node->x = ft_atoi(params[1]);
		node->y = ft_atoi(params[2]);
	}
	else
		error("Room's coordinates must be integers", lem);
	ft_strdel(&itoa1);
	ft_strdel(&itoa2);
	node->links = NULL;
	ft_arrclr(params);
	return (node);
}