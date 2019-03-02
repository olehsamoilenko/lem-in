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

void	mark_path(t_list_of_nodes *path)
{
	while (path)
	{
		path->node->bfs_used = 1;
		path = path->next;
	}
}

t_list_of_nodes *form_path(t_node *node, t_lem *lem)
{
	t_list_of_nodes *path = NULL;

	while (node)
	{
		push_node(&path, node, lem);
		node = node->bfs_prev;
	}
	return (path);
}

void reset_nodes_in_queue(t_list_of_nodes *nodes, t_lem *lem)
{
	while (nodes)
	{
		nodes->node->bfs_in_queue = 0;
		nodes->node->bfs_prev = NULL;
		nodes = nodes->next;
	}
	
}

t_list_of_nodes *bfs(t_node *start, t_node *end, t_lem *lem)
{
	t_list_of_nodes *queue = create_list_of_nodes(start); // mb node_push ?
	reset_nodes_in_queue(lem->nodes, lem);
	end->bfs_used = 0;
	start->bfs_in_queue = 1;

	// show_all_nodes(lem->nodes, lem);

	while(queue)
	{
		t_node *node = pop_node(&queue);
		if (node == end)
		{
			t_list_of_nodes *path = form_path(end, lem);
			mark_path(path);
			delete_path(queue);
			return (path);
		}
		else
		{
			t_list_of_nodes *tmp = node->links;
			while (tmp)
			{
				if (tmp->node->bfs_in_queue == 0 && tmp->node->bfs_used == 0)
				{
					push_node(&queue, tmp->node, lem);
					tmp->node->bfs_in_queue = 1;
					tmp->node->bfs_prev = node;;
				}
				tmp = tmp->next;
			}
		}
	}
	return (NULL);
}

t_list_of_nodes *bfs_less_links_oriented(t_node *start, t_node *end, t_lem *lem)
{
	t_list_of_nodes *queue = create_list_of_nodes(start);
	reset_nodes_in_queue(lem->nodes, lem);

	end->bfs_used = 0;
	start->bfs_in_queue = 1;
	while(queue)
	{
		t_node *node = pop_node(&queue);
		if (node == end)
		{
			t_list_of_nodes *path = form_path(end, lem);
			mark_path(path);
			delete_path(queue);

			return (path);
		}
		else
		{
			t_list_of_nodes *tmp = node->links;
			int node_pushed = 0;
			while (tmp)
			{
				if (tmp->node->bfs_in_queue == 0 && tmp->node->bfs_used == 0)
				{
					// printf("%s\n", tmp->node->name);
					if (tmp->next == NULL && node_pushed != 0)
					{
						// printf("%s skipped\n", tmp->next->node->name);
					}
					else
					{
						push_node(&queue, tmp->node, lem);

						tmp->node->bfs_in_queue = 1;
						tmp->node->bfs_prev = node;
						
						if (tmp->node->links->node != node) ////// work ?????????????
							node_pushed += 1;
					}
					if (tmp->node == end)
						break;
				}
				tmp = tmp->next;
			}
		}
	}
	return (NULL);
}