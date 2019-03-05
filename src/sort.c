/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 15:31:49 by osamoile          #+#    #+#             */
/*   Updated: 2018/08/24 15:31:50 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	swap_nodes(t_node **link_1, t_node **link_2)
{
	t_node *tmp = *link_1;
	*link_1 = *link_2;
	*link_2 = tmp;
}

void	sort_links(t_list_of_nodes *nodes, t_lem *lem)
{
	if (!nodes)
		return;
	t_list_of_nodes *tmp = nodes;
	while (tmp)
	{
		t_list_of_nodes *start = nodes;
		while (start->next)
		{
			if (path_len(start->node->links) > path_len(start->next->node->links))
				swap_nodes(&start->node, &start->next->node);
			// if (start->next->node ==)
			start = start->next;
		}
		tmp = tmp->next;
	}
}

void	sort_nodes_by_amount_of_links(t_list_of_nodes *nodes, t_lem *lem)
{
	while (nodes)
	{
		sort_links(nodes->node->links, lem);
		nodes = nodes->next;
	}
}

void	swap_lists(t_list_of_nodes **path_1, t_list_of_nodes **path_2)
{
	t_list_of_nodes *tmp = *path_1;
	*path_1 = *path_2;
	*path_2 = tmp;
}void	sort_pathes_by_len(t_list_of_pathes *pathes)
{
	if (!pathes)
		return;
	t_list_of_pathes *tmp = pathes;
	while (tmp)
	{
		t_list_of_pathes *start = pathes;
		while (start->next)
		{
			if (path_len(start->path) > path_len(start->next->path))
				swap_lists(&start->path, &start->next->path);
			start = start->next;
		}
		tmp = tmp->next;
	}
}