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

#include "lemin.h"

int				node_in_path(t_list_of_nodes *path, t_node *node)
{
	while (path != NULL)
	{
		if (path->node == node)
			return (1);
		path = path->next;
	}
	return (0);
}

static t_node	*find_node(char *name, t_list_of_nodes *nodes)
{
	while (nodes)
	{
		if (ft_strequ(name, nodes->node->name))
			return (nodes->node);
		nodes = nodes->next;
	}
	return (NULL);
}

void			create_link(char *line, t_lem *lem)
{
	char	**params;
	t_node	*n1;
	t_node	*n2;

	params = ft_strsplit(line, '-');
	if (ft_char_count(' ', line) != 0 || ft_arrlen(params) != 2)
		error("Link definition example: room_1-room_2", lem);
	n1 = find_node(params[0], lem->nodes);
	n2 = find_node(params[1], lem->nodes);
	ft_arrclr(params);
	if (n1 == NULL || n2 == NULL)
		error("Link contains an unknown room", lem);
	if (n1 == n2)
		error("Self-loops are forbidden", lem);
	if (!node_in_path(n1->links, n2) && !node_in_path(n2->links, n1))
	{
		push_node(&n1->links, n2);
		push_node(&n2->links, n1);
	}
	else
		error("Link duplication is forbidden", lem);
}
