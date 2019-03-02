/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 15:31:49 by osamoile          #+#    #+#             */
/*   Updated: 2018/08/24 15:31:50 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		path_contains_node(t_list_of_nodes *path, t_node *node) //rename
{
	while (path != NULL)
	{
		if (path->node == node)
			return (1);
		path = path->next;
	}
	return (0);
}

t_node	*find_node(char *name, t_list_of_nodes *nodes) // rename
{
	int i = -1;
	// t_list_of_nodes *start = nodes;
	while (nodes)
	{
		if (ft_strequ(name, nodes->node->name))
			return (nodes->node);
		nodes = nodes->next;
	}
	// nodes = start;
	return (NULL);
}

void	create_link(char *line, t_lem *lem)
{
	char **params = ft_strsplit(line, '-');
	if (ft_char_count(' ', line) != 0 || ft_arrlen(params) != 2)
		error("Link definition example: room_1-room_2", lem);
	t_node *n1 = find_node(params[0], lem->nodes);
	t_node *n2 = find_node(params[1], lem->nodes);
	ft_arrclr(params);
	if (n1 == NULL || n2 == NULL)
		error("Link contains an unknown room", lem);
	if (n1 == n2)
		error("Self-loops are forbidden", lem);
	if (!path_contains_node(n1->links, n2) && !path_contains_node(n2->links, n1))
	{
		push_node(&n1->links, n2, lem);
		push_node(&n2->links, n1, lem);
	}
	else
	{
		error("Link duplication is forbidden", lem);
	}
	
		
}