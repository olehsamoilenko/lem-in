/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 15:31:49 by osamoile          #+#    #+#             */
/*   Updated: 2018/08/24 15:31:50 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_list_of_nodes	*form_path(t_node *node)
{
	t_list_of_nodes *path;

	path = NULL;
	while (node)
	{
		push_node(&path, node);
		node->bfs_used = 1;
		node = node->bfs_prev;
	}
	return (path);
}

void					reset_nodes_in_queue(t_list_of_nodes *nodes, t_lem *lem)
{
	while (nodes)
	{
		nodes->node->bfs_in_queue = 0;
		nodes->node->bfs_prev = NULL;
		nodes = nodes->next;
	}
	lem->start->bfs_used = 0;
	lem->end->bfs_in_queue = 1;
}

static void				work_with_links(t_list_of_nodes *links,
						t_list_of_nodes **queue, t_node *prev)
{
	while (links)
	{
		if (links->node->bfs_in_queue == 0 && links->node->bfs_used == 0)
		{
			push_node(queue, links->node);
			links->node->bfs_in_queue = 1;
			links->node->bfs_prev = prev;
		}
		links = links->next;
	}
}

static void				work_with_links_2(t_list_of_nodes *links,
						t_list_of_nodes **queue, t_node *prev)
{
	int node_pushed;

	node_pushed = 0;
	while (links)
	{
		if (links->node->bfs_in_queue == 0 && links->node->bfs_used == 0)
		{
			if (links->next != NULL || !node_pushed)
			{
				push_node(queue, links->node);
				links->node->bfs_in_queue = 1;
				links->node->bfs_prev = prev;
				if (links->node->links->node != prev)
					node_pushed = 1;
			}
		}
		links = links->next;
	}
}

t_list_of_nodes			*bfs(t_lem *lem, int mode)
{
	t_list_of_nodes *queue;
	t_node			*node;

	queue = create_list_of_nodes(lem->end);
	reset_nodes_in_queue(lem->nodes, lem);
	while (queue)
	{
		node = pop_node(&queue);
		if (node == lem->start)
		{
			delete_path(queue);
			return (form_path(lem->start));
		}
		else
		{
			if (mode == 0)
				work_with_links(node->links, &queue, node);
			else if (mode == 1)
				work_with_links_2(node->links, &queue, node);
		}
	}
	return (NULL);
}
