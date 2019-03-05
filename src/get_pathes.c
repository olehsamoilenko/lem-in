/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pathes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 15:31:49 by osamoile          #+#    #+#             */
/*   Updated: 2018/08/24 15:31:50 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		remove_node(t_list_of_nodes **list, t_node *node)
{
	t_list_of_nodes *tmp;
	t_list_of_nodes *start;

	tmp = NULL;
	if ((*list)->node == node)
	{
		tmp = *list;
		*list = (*list)->next;
	}
	else
	{
		start = *list;
		while ((*list)->next)
		{
			if ((*list)->next->node == node)
			{
				tmp = (*list)->next;
				(*list)->next = (*list)->next->next;
				break ;
			}
			*list = (*list)->next;
		}
		*list = start;
	}
	free(tmp);
}

static void	start_to_end_handle(t_lem *lem, t_list_of_pathes **pathes_1,
		t_list_of_pathes **pathes_2)
{
	t_list_of_nodes *path;

	if (node_in_path(lem->start->links, lem->end))
	{
		path = NULL;
		push_node(&path, lem->start);
		push_node(&path, lem->end);
		push_path(pathes_1, path);
		push_path(pathes_2, path);
		remove_node(&lem->start->links, lem->end);
		remove_node(&lem->end->links, lem->start);
	}
}

static void	reset_used_nodes(t_list_of_nodes *list, t_lem *lem)
{
	reset_nodes_in_queue(list, lem);
	while (list)
	{
		list->node->bfs_used = 0;
		list = list->next;
	}
}

void		get_pathes(t_list_of_pathes **pathes_1, t_list_of_pathes **pathes_2,
			t_lem *lem)
{
	t_list_of_nodes *path;

	start_to_end_handle(lem, pathes_1, pathes_2);
	while ((path = bfs(lem, BFS_ORIGINAL)))
		push_path(pathes_1, path);
	reset_used_nodes(lem->nodes, lem);
	sort_nodes_by_amount_of_links(lem->nodes);
	while ((path = bfs(lem, BFS_LESS_LINKS)))
		push_path(pathes_2, path);
	sort_pathes_by_len(*pathes_2);
	if (!*pathes_1 && !*pathes_2)
		error("Not enough data to process", lem);
}
