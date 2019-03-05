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

#include "lemin.h"

static void	swap_nodes(t_node **link_1, t_node **link_2)
{
	t_node *tmp;

	tmp = *link_1;
	*link_1 = *link_2;
	*link_2 = tmp;
}

static void	sort_links(t_list_of_nodes *nodes)
{
	t_list_of_nodes *tmp;
	t_list_of_nodes *start;

	if (!nodes)
		return ;
	tmp = nodes;
	while (tmp)
	{
		start = nodes;
		while (start->next)
		{
			if (path_len(start->node->links) >
				path_len(start->next->node->links))
				swap_nodes(&start->node, &start->next->node);
			start = start->next;
		}
		tmp = tmp->next;
	}
}

void		sort_nodes_by_amount_of_links(t_list_of_nodes *nodes)
{
	while (nodes)
	{
		sort_links(nodes->node->links);
		nodes = nodes->next;
	}
}

static void	swap_pathes(t_list_of_nodes **path_1, t_list_of_nodes **path_2)
{
	t_list_of_nodes *tmp;

	tmp = *path_1;
	*path_1 = *path_2;
	*path_2 = tmp;
}

void		sort_pathes_by_len(t_list_of_pathes *pathes)
{
	t_list_of_pathes *start;
	t_list_of_pathes *tmp;

	if (!pathes)
		return ;
	tmp = pathes;
	while (tmp)
	{
		start = pathes;
		while (start->next)
		{
			if (path_len(start->path) > path_len(start->next->path))
				swap_pathes(&start->path, &start->next->path);
			start = start->next;
		}
		tmp = tmp->next;
	}
}
