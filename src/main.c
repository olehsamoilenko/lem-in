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
#include <stdio.h>

#define MAP_ROOMS_MODE 0
#define MAP_LINKS_MODE 1
#define GNL_READ_MODE 0
#define GNL_RETURN_COUNT_MODE 1

void	show_node(t_node *node, t_lem *lem)
{
	if (lem->start == node)
		printf("START:");
	else if (lem->end == node)
		printf("END:");
	printf("\tname: %s,\t", node->name);
	if (node->bfs_prev == NULL)
		printf("prev: -,");
	else
		printf("prev: %s,", node->bfs_prev->name);
	printf("\tin_queue: %d,\tbfs_used: %d,\tlinks: ",
		node->bfs_in_queue, node->bfs_used);

	
	t_list_of_nodes *start = node->links;
	while (node->links)
	{
		printf("%s ", node->links->node->name);
		node->links = node->links->next;
	}
	node->links = start;
	printf("\n");
}
void	show_all_nodes(t_list_of_nodes *list, t_lem *lem)
{
	printf("ALL NODES:\n");
	t_list_of_nodes *start = list;
	while (list)
	{
		show_node(list->node, lem);
		list = list->next;
	}
	list = start;
	printf("\n");
}

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

int		get_next_line_counter(int mode, int fd, char **line)
{
	static int count = 0;
	if (mode == GNL_READ_MODE)
	{
		count++;
		int res = get_next_line(fd, line);
		if (res)
			printf("%s\n", *line);
		return (res);
	}
	else if (mode == GNL_RETURN_COUNT_MODE)
		return (count);
	else return (0);
}

void	error(char *message, t_lem *lem)
{
	ft_printf("ERROR line %d: %s\n",
		get_next_line_counter(GNL_RETURN_COUNT_MODE, 0, NULL), message);
	show_all_nodes(lem->nodes, lem);
	system("leaks lem-in");
	exit(0);
}

int		ft_arrlen(char **arr)
{
	int i = 0;
	if (arr == NULL)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

int		ft_char_count(char c, char *line)
{
	int i = -1;
	int res = 0;
	while (line[++i])
	{
		if (line[i] == c)
			res++;
	}
	return (res);
}

int		path_contains_node(t_list_of_nodes *path, t_node *node)
{
	while (path != NULL)
	{
		if (path->node == node)
			return (1);
		path = path->next;
	}
	return (0);
}

t_node	*find_node(char *name, t_list_of_nodes *nodes)
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
	printf("ants: %d\t\t", path->ants);
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

	int res = (lem->ants + l) / k - 1;
	if ((lem->ants + l) % k != 0)
		res += 1;
	return (res);
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

t_list_of_nodes	*create_list_of_nodes(t_node *first_node)
{
	t_list_of_nodes *list = ft_memalloc(sizeof(t_list_of_nodes));
	list->node = first_node;
	list->next = NULL;
	return (list);
}

t_list_of_pathes *create_list_of_pathes(t_list_of_nodes *first_path)
{
	t_list_of_pathes *list = ft_memalloc(sizeof(t_list_of_pathes));
	list->path = first_path;
	list->next = NULL;
	return (list);
}

// void		check_parameters_equalness(t_node *node_1, t_node *node_2, t_lem *lem)
// {
// 	if (ft_strequ(node_1->name, node_2->name))
// 		error("Room's name must be unique", lem);
// 	if (node_1->x == node_2->x && node_1->y == node_2->y)
// 		error("Room's coordinates must be unique", lem);
// }

void	push_node(t_list_of_nodes **list, t_node *node, t_lem *lem)
{
	
	if (*list == NULL)
		*list = create_list_of_nodes(node);
	else
	{
		t_list_of_nodes *start = *list;

		while ((*list)->next != NULL)
		{
			
			// check_parameters_equalness((*list)->node, node, lem);
			*list = (*list)->next;
		}
		// check_parameters_equalness((*list)->node, node, lem);
	
		(*list)->next = ft_memalloc(sizeof(t_list_of_nodes));
		(*list)->next->node = node;
		(*list)->next->next = NULL;
		*list = start;
	}
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

t_node	*create_node(char *line, t_lem *lem)
{
	char *itoa1;
	char *itoa2;
	char **params = ft_strsplit(line, ' ');

	if (ft_arrlen(params) != 3 || ft_char_count(' ', line) != 2)
		error("Room definition example: 'name x y'", lem);
	if (params[0][0] == 'L')
		error("Room's name must not start with the character 'L'", lem);
	if (ft_char_count('-', params[0]) != 0)
		error("Room's name must not contain the character '-'", lem);
	

	t_node	*node = ft_memalloc(sizeof(t_node));
	node->name = ft_strdup(params[0]);
	node->bfs_used = 0;
	node->bfs_in_queue = 0;
	node->bfs_prev = NULL;
	node->ant_id = 0;
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
	if (!path_contains_node(n1->links, n2))
		push_node(&n1->links, n2, lem);
	if (!path_contains_node(n2->links, n1))
		push_node(&n2->links, n1, lem);
}

void	read_map(t_lem *lem)
{
	char *line;
	int mode = MAP_ROOMS_MODE;
	
	get_next_line_counter(GNL_READ_MODE, 0, &line);
	char *itoa = ft_itoa(ft_atoi(line));
	if (ft_strequ(itoa, line) && ft_atoi(line) > 0)
		lem->ants = ft_atoi(line);
	else
		error("Number of ants must be a positive integer", lem);
	ft_strdel(&itoa);
	ft_strdel(&line);
	while (get_next_line_counter(GNL_READ_MODE, 0, &line))
	{
		if (ft_strequ(line, "##start"))
		{
			ft_strdel(&line);
			get_next_line_counter(GNL_READ_MODE, 0, &line);
			t_node *buf = create_node(line, lem);
			push_node(&lem->nodes, buf, lem);
			if (lem->start != NULL)
				error("Too much start rooms", lem);
			lem->start = buf;
		}
		else if (ft_strequ(line, "##end"))
		{
			
			ft_strdel(&line);
			get_next_line_counter(GNL_READ_MODE, 0, &line);
			t_node *buf = create_node(line, lem);
			push_node(&lem->nodes, buf, lem);
			if (lem->end != NULL)
				error("Too much end rooms", lem);
			lem->end = buf;
		}
		else if (line[0] == '#')
		{
			// printf("%s skipped\n", line);
		}
		else if (mode == MAP_LINKS_MODE || ft_strchr(line, '-'))
		{
			create_link(line, lem);
			mode = MAP_LINKS_MODE;
		}
		else if (mode == MAP_ROOMS_MODE)
			push_node(&lem->nodes, create_node(line, lem), lem);
		ft_strdel(&line);
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

void	mark_path(t_list_of_nodes *path)
{
	// t_list_of_nodes *path = NULL;

	while (path)
	{
		// push_node(&path, node, lem);
		path->node->bfs_used = 1;

		path = path->next;
	}
	// return (path);
}

t_list_of_nodes *form_path(t_node *node, t_lem *lem)
{
	t_list_of_nodes *path = NULL;

	while (node)
	{
		push_node(&path, node, lem);
		// node->bfs_used = 1;
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
	t_list_of_nodes *queue = create_list_of_nodes(start);
	reset_nodes_in_queue(lem->nodes, lem);
	end->bfs_used = 0;
	start->bfs_in_queue = 1;

	while(queue)
	{
		
		t_node *node = pop_node(&queue);
		// printf("got %s from queue\n", node->name);
		if (node == end)
		{
			// printf("\tfound start\n");
			
			t_list_of_nodes *path = form_path(end, lem);
			mark_path(path);
			// show_path(path);
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
					tmp->node->bfs_prev = node;
					// printf("%s put %s to queue\n", node->name, tmp->node->name);
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
		// printf("pop from queue:\t"); show_node(node, lem);
		if (node == end)
		{
			// printf("\tfound start\n");
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
					if (tmp->next != NULL || node_pushed == 0)
					{
						push_node(&queue, tmp->node, lem);
						tmp->node->bfs_in_queue = 1;
						tmp->node->bfs_prev = node;
						// printf("%s put %s to queue\n", node->name, tmp->node->name);
						node_pushed += 1;
					}
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
void	sort_links(t_list_of_nodes *nodes)
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
			start = start->next;
		}
		tmp = tmp->next;
	}
}
void	sort_nodes_by_amount_of_links(t_list_of_nodes *nodes)
{
	while (nodes)
	{
		sort_links(nodes->node->links);
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

void	new_ants(t_list_of_ants **ants, t_list_of_pathes *pathes, int *ant_counter, t_lem *lem)
{
	while (pathes && *ant_counter <= lem->ants)
	{
		push_ant(ants, (*ant_counter)++, pathes->path, lem);
		pathes = pathes->next;
	}

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

	int ant_counter = 1;

	new_ants(&ants, pathes, &ant_counter, lem);
	while (ants)
	{
		step(ants, lem);
		// show_all_ants(ants);
		show_steps(ants);
		remove_finishers(&ants, lem);
		new_ants(&ants, pathes, &ant_counter, lem);
	}
	
	delete_list_of_ants(ants);
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
	// show_all_pathes(lem->pathes_1, lem);
	
	reset_used_nodes(lem->nodes, lem);
	sort_nodes_by_amount_of_links(lem->nodes);

	while ((path = bfs_less_links_oriented(lem->end, lem->start, lem)))
		push_path(&lem->pathes_2, path);
	// show_all_pathes(lem->pathes_2, lem);
	
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
