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

#include "lem-in.h"

t_list_of_nodes	*form_path(t_node *node, t_lem *lem)
{
	t_list_of_nodes *path = NULL;

	while (node)
	{
		push_node(&path, node);
		node->bfs_used = 1;
		node = node->bfs_prev;
	}
	return (path);
}

void			reset_nodes_in_queue(t_list_of_nodes *nodes, t_lem *lem)
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

void			work_with_links(t_list_of_nodes *links, t_list_of_nodes **queue, t_node *prev)
{
	while (links)
	{
		if (links->node->bfs_in_queue == 0 && links->node->bfs_used == 0)
		{
			push_node(queue, links->node);
			links->node->bfs_in_queue = 1;
			links->node->bfs_prev = prev;;
		}
		links = links->next;
	}
}

t_list_of_nodes *bfs(t_lem *lem)
{
	t_list_of_nodes *queue = create_list_of_nodes(lem->end); // mb node_push ?
	reset_nodes_in_queue(lem->nodes, lem);
	
	while(queue)
	{
		t_node *node = pop_node(&queue);
		if (node == lem->start)
		{
			delete_path(queue);
			return (form_path(lem->start, lem));
		}
		else
			work_with_links(node->links, &queue, node);
	}
	return (NULL);
}



t_list_of_nodes	*bfs_less_links_oriented(t_lem *lem)
{
	t_list_of_nodes *queue = create_list_of_nodes(lem->end);
	reset_nodes_in_queue(lem->nodes, lem);

	while(queue)
	{
		int node_pushed = 0;
		t_node *node = pop_node(&queue);
		if (node == lem->start)
		{
			delete_path(queue);
			return (form_path(lem->start, lem));
		}
		else
		{
			t_list_of_nodes *tmp = node->links;
			
			while (tmp)
			{
				if (tmp->node->bfs_in_queue == 0 && tmp->node->bfs_used == 0)
				{
					if (tmp->next != NULL || !node_pushed)
					{
						push_node(&queue, tmp->node);
						tmp->node->bfs_in_queue = 1;
						tmp->node->bfs_prev = node;
						if (tmp->node->links->node != node) ////// work ?????????????
							node_pushed = 1;
					}
				}
				tmp = tmp->next;
			}
		}
	}
	return (NULL);
}
