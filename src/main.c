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
		printf("START: ");
	else if (lem->end == node)
		printf("END: ");
	printf("name: %s, ", node->name);
	if (node->bfs_prev == NULL)
		printf("prev: null,\t");
	else
		printf("prev: %s, ", node->bfs_prev->name);
	printf("bfs_dist: %d, bfs_path_id: %d, bfs_used: %d, links: ",
		node->bfs_dist, node->bfs_path_id, node->bfs_used);

	
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
	lem->pathes = NULL;
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
		return(get_next_line(fd, line));
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
	printf("Length: %d\t", path_len(path));
	while (1)
	{
		printf("%s", path->node->name);
		if (path->next != NULL)
		{
			printf("->");
			path = path->next;
		}
		else
			break;
	}
	printf("\n");
}
void	show_all_pathes(t_list_of_pathes *list)
{
	printf("ALL PATHES:\n");
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

void	add_node_to_list_back(t_list_of_nodes **list, t_node *node, t_lem *lem)
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

void	add_path_to_list(t_list_of_pathes **list, t_list_of_nodes *path)
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
		
		add_node_to_list_back(&new_path, path->node, lem);
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
	node->bfs_dist = -1;
	node->bfs_path_id = -1;
	node->bfs_used = 0;
	node->bfs_in_queue = 0;
	node->bfs_prev = NULL;
	// node->bfs_marked = 0;
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
		add_node_to_list_back(&n1->links, n2, lem);
	if (!path_contains_node(n2->links, n1))
		add_node_to_list_back(&n2->links, n1, lem);
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
			add_node_to_list_back(&lem->nodes, buf, lem);
			if (lem->start != NULL)
				error("Too much start rooms", lem);
			lem->start = buf;
		}
		else if (ft_strequ(line, "##end"))
		{
			
			ft_strdel(&line);
			get_next_line_counter(GNL_READ_MODE, 0, &line);
			t_node *buf = create_node(line, lem);
			add_node_to_list_back(&lem->nodes, buf, lem);
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
			add_node_to_list_back(&lem->nodes, create_node(line, lem), lem);
		ft_strdel(&line);
	}
}

t_node	*pop_front(t_list_of_nodes **list)
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

t_list_of_nodes		*form_path(t_node *node, t_lem *lem)
{
	// show_all_nodes(lem->nodes, lem);
	t_list_of_nodes *path = NULL;
	while (node)
	{
		if (node->bfs_used == 1)
		{
			printf("path contains already used nodes: %s\n", node->name);
			delete_path(path);
			return (NULL);
		}
		node->bfs_used += 1;
		add_node_to_list_back(&path, node, lem);
		node = node->bfs_prev;
	}
	return (path);
}

// void	clear_queue(t_list_of_nodes *queue)
// {
// 	while (queue)
// 	{
// 		queue->node->bfs_used = 0;
// 		queue->node->bfs_prev = NULL;
// 		queue = queue->next;
// 	}
// }

void	bfs(t_lem *lem)
{
	t_list_of_nodes *queue = create_list_of_nodes(lem->end);
	lem->end->bfs_in_queue = 1;
	lem->end->bfs_prev = NULL;
	t_node *curr;
	t_list_of_nodes *links;

	while (queue)
	{
		curr = pop_front(&queue);
		links = curr->links;
		while (links)
		{
			if (links->node->bfs_in_queue == 0)
			{
				links->node->bfs_in_queue += 1;
				links->node->bfs_prev = curr;
				if (links->node == lem->start)
				{
					printf("path forming: ");
					t_list_of_nodes *path = form_path(lem->start, lem);
					show_path(path);
					delete_path(path);
					lem->start->bfs_in_queue = 0;
					lem->start->bfs_used = 0;
					lem->end->bfs_used = 0;
					lem->start->bfs_prev = NULL;

					// printf("Nodes: ");
					// show_all_nodes(lem->nodes, lem);
				}
				else
					add_node_to_list_back(&queue, links->node, lem);
			}
			links = links->next;
		}
		printf("Queue: ");
		show_all_nodes(queue, lem);
	}
	delete_path(queue);
}

int		main(void)
{
	t_lem *lem = init();
	read_map(lem);

	if (lem->start == NULL)
		error("The start room is missing", lem);
	if (lem->end == NULL)
		error("The end room is missing", lem);

	

	bfs(lem);

	show_all_nodes(lem->nodes, lem);


	system("leaks lem-in");
	return (0);
}
