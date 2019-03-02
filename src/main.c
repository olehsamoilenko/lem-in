/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 15:31:49 by osamoile          #+#    #+#             */
/*   Updated: 2018/08/24 15:31:50 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

t_lem	*init()
{
	t_lem *lem = ft_memalloc(sizeof(t_lem));
	lem->nodes = NULL;
	lem->pathes_1 = NULL;
	lem->pathes_2 = NULL;
	lem->start = NULL;
	lem->end = NULL;
	return (lem);
}







int		path_len(t_list_of_nodes *list)
{
	int i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i - 1);
}


void	show_path(t_list_of_nodes *path)
{
	if (path == NULL)
	{
		printf("Path is clear\n");
		return;
	}
	while (1)
	{
		printf("%s", path->node->name);
		if (path->next == NULL)
			break;
		else
			printf("->");
		path = path->next;
	}
	printf("\n");
}

int		total_len(t_list_of_pathes *list)
{
	int len = 0;
	while (list)
	{
		len += path_len(list->path);
		list = list->next;
	}
	return (len);
}

int		list_len(t_list_of_pathes *list)
{
	int res = 0;
	while (list)
	{
		res++;
		list = list->next;
	}
	return (res);
}

int		total_steps(t_list_of_pathes *list, t_lem *lem)
{
	int l = total_len(list);
	int k = list_len(list);

	if (k == 0)
		return (__INT_MAX__);

	int res = (lem->ants + l) / k - 1;
	if ((lem->ants + l) % k != 0)
		res += 1;
	return (res);

	// return (-1);
}

void	show_all_pathes(t_list_of_pathes *list, t_lem *lem)
{
	printf("ALL PATHES (total_steps = %d):\n", total_steps(list, lem));
	t_list_of_pathes *start = list;
	while (list)
	{
		show_path(list->path);
		list = list->next;
	}
	list = start;
	printf("\n");
}



t_list_of_pathes *create_list_of_pathes(t_list_of_nodes *first_path)
{
	t_list_of_pathes *list = ft_memalloc(sizeof(t_list_of_pathes));
	list->path = first_path;
	list->next = NULL;
	return (list);
}



void	push_path(t_list_of_pathes **list, t_list_of_nodes *path)
{
	if (*list == NULL)
	{
		*list = create_list_of_pathes(path);
	}
	else
	{
		t_list_of_pathes *start = *list;
		while ((*list)->next != NULL)
			*list = (*list)->next;
		(*list)->next = ft_memalloc(sizeof(t_list_of_pathes));
		(*list)->next->path = path;
		(*list)->next->next = NULL;
		*list = start;
	}
}

t_list_of_nodes	*copy_list_of_nodes(t_list_of_nodes *path, t_lem *lem)
{
	// t_list_of_nodes *start = path;
	t_list_of_nodes	*new_path = NULL;
	while (path != NULL)
	{
		
		push_node(&new_path, path->node, lem);
		path = path->next;
	}
	// path = start;
	return(new_path);
}

void	delete_path(t_list_of_nodes *path)
{
	t_list_of_nodes *start = path;
	if (path == NULL)
		return;
	while ((path)->next != NULL)
	{
		while ((path)->next->next != NULL)
			path = (path)->next;
		free((path)->next);
		(path)->next = NULL;
		path = start;
	}
	free(path);
	// path = NULL;
	
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


void reset_used_nodes(t_list_of_nodes *list, t_lem *lem)
{
	reset_nodes_in_queue(list, lem);
	while (list)
	{	
		list->node->bfs_used = 0;
		list = list->next;
	}
}

// sorting
void	swap_links(t_node **link_1, t_node **link_2)
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
				swap_links(&start->node, &start->next->node);
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
// sorting

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

void	start_to_end_handle(t_lem *lem)
{
	if (path_contains_node(lem->start->links, lem->end))
	{
		t_list_of_nodes *path = NULL;
		push_node(&path, lem->start, lem);
		push_node(&path, lem->end, lem);
		push_path(&lem->pathes_1, path);
		push_path(&lem->pathes_2, path);
		remove_node(&lem->start->links, lem->end);
		remove_node(&lem->end->links, lem->start);
	}
}

t_list_of_ants	*create_list_of_ants(int num, t_list_of_nodes *ant_position)
{
	t_list_of_ants *ants = ft_memalloc(sizeof(t_list_of_ants));
	ants->ant_id = num;
	ants->position = ant_position;
	ants->next = NULL;
	return (ants);
}

void	show_all_ants(t_list_of_ants *ants)
{
	while (ants)
	{
		printf("id: %d\tposition: %s\n", ants->ant_id, ants->position->node->name);
		ants = ants->next;
	}
	printf("\n");
}

void	push_ant(t_list_of_ants **ants, int num, t_list_of_nodes *ant_position, t_lem *lem)
{
	if (*ants == NULL)
		*ants = create_list_of_ants(num, ant_position);
	else
	{
		t_list_of_ants *start = *ants;

		while ((*ants)->next != NULL)
		{
			
			// check_parameters_equalness((*list)->node, node, lem);
			*ants = (*ants)->next;
		}
		// check_parameters_equalness((*list)->node, node, lem);
	
		(*ants)->next = ft_memalloc(sizeof(t_list_of_ants));
		(*ants)->next->ant_id = num;
		(*ants)->next->position = ant_position;
		(*ants)->next->next = NULL;
		*ants = start; // fix
	}
}

void	delete_list_of_ants(t_list_of_ants *ants)
{
	t_list_of_ants *start = ants; // ?
	if (ants == NULL)
		return;
	while ((ants)->next != NULL)
	{
		while ((ants)->next->next != NULL)
			ants = (ants)->next;
		free((ants)->next);
		(ants)->next = NULL;
		ants = start;
	}
	free(ants);
	// path = NULL;
	
}

// void	new_ants(t_list_of_ants **ants, t_list_of_pathes *pathes, int *ant_counter, t_lem *lem)
// {
// 	while (pathes && *ant_counter <= lem->ants)
// 	{
// 		push_ant(ants, (*ant_counter)++, pathes->path, lem);
// 		pathes = pathes->next;
// 	}

// }


void	new_ants(t_list_of_ants **ants, t_list_of_pathes *pathes, int *ant_counter, t_lem *lem)
{
	t_list_of_pathes *start = pathes;
	while (pathes && lem->ants - *ant_counter != 0)
	{
		t_list_of_pathes *tmp = start;
		int shorter_ways_sum = 0;
		while (tmp != pathes)
		{
			shorter_ways_sum += path_len(pathes->path) - path_len(tmp->path);
			tmp = tmp->next;
		}

		// printf("ants: %d\n", lem->ants - *ant_counter);
		if (lem->ants - *ant_counter > shorter_ways_sum)
		{
			
			(*ant_counter)++;

			// printf("\t%d choose ", *ant_counter); show_path(pathes->path);

			push_ant(ants, *ant_counter, pathes->path, lem);


		}

		
			
		

		pathes = pathes->next;
		
	}
	pathes = start;
	

}

void	step(t_list_of_ants *ants, t_lem *lem)
{
	t_list_of_ants *buf = ants;
	while (buf)
	{
		buf->position = buf->position->next;
		buf = buf->next;
	}
}


void	remove_ant(t_list_of_ants **ants, t_list_of_ants *ant)
{
	t_list_of_ants *tmp;
	
	if (*ants == ant)
	{
		tmp = *ants;
		*ants = (*ants)->next;
	}
	else
	{
		t_list_of_ants *start = *ants;
		while ((*ants)->next)
		{
			if ((*ants)->next == ant)
			{
				tmp = (*ants)->next;
				(*ants)->next = (*ants)->next->next;
				break;
			}
			*ants = (*ants)->next;
		}
		*ants = start;
	}
	free(tmp);
}

void	remove_finishers(t_list_of_ants **ants, t_lem *lem)
{
	t_list_of_ants *tmp = *ants;
	while (tmp)
	{
		if (tmp->position->node == lem->end)
			remove_ant(ants, tmp);
		tmp = tmp->next;
	}
}

void	show_steps(t_list_of_ants *ants)
{
	while (ants)
	{
		printf("L%d-%s ", ants->ant_id, ants->position->node->name);
		ants = ants->next;
	}
	printf("\n");
}


void	ants_contribution(t_list_of_pathes *pathes, t_lem *lem)
{
	t_list_of_ants *ants = NULL;

	int ant_counter = 0;

	new_ants(&ants, pathes, &ant_counter, lem);
	while (ants)
	{
		step(ants, lem);

		show_steps(ants);

		remove_finishers(&ants, lem);
		new_ants(&ants, pathes, &ant_counter, lem);
	}
	delete_list_of_ants(ants);
}

// sorting
void	swap_lists(t_list_of_nodes **path_1, t_list_of_nodes **path_2)
{
	t_list_of_nodes *tmp = *path_1;
	*path_1 = *path_2;
	*path_2 = tmp;
}
void	sort_list(t_list_of_pathes *pathes)
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

int		main(void)
{
	t_lem *lem = init();
	read_map(lem);
	printf("\n");

	if (lem->start == NULL)
		error("The start room is missing", lem);
	if (lem->end == NULL)
		error("The end room is missing", lem);


	
	start_to_end_handle(lem);


	t_list_of_nodes *path;
	while ((path = bfs(lem->end, lem->start, lem)))
		push_path(&lem->pathes_1, path);

	

	
	reset_used_nodes(lem->nodes, lem);
	sort_nodes_by_amount_of_links(lem->nodes, lem);



	while ((path = bfs_less_links_oriented(lem->end, lem->start, lem)))
		push_path(&lem->pathes_2, path);
	sort_list(lem->pathes_2);




	if (!lem->pathes_1 && !lem->pathes_2)
		error("Not enough data to process", lem);
	
	t_list_of_pathes *pathes;
	if (total_steps(lem->pathes_1, lem) <= total_steps(lem->pathes_2, lem))
		pathes = lem->pathes_1;
	else
		pathes = lem->pathes_2;

	show_all_pathes(pathes, lem);

	ants_contribution(pathes, lem);
	
	system("leaks lem-in");
	return (0);
}
