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
	if (lem->end == node)
		printf("END: ");
	printf("%s, (%d,%d), links: ", node->name, node->x, node->y);
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
	printf("Length: %d, group %d: ", path_len(path), path->group);
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
	list->group = 0;
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

void		check_parameters_equalness(t_node *node_1, t_node *node_2, t_lem *lem)
{
	if (ft_strequ(node_1->name, node_2->name))
		error("Room's name must be unique", lem);
	if (node_1->x == node_2->x && node_1->y == node_2->y)
		error("Room's coordinates must be unique", lem);
}

void	add_node_to_list(t_list_of_nodes **list, t_node *node, t_lem *lem)
{
	
	if (*list == NULL)
		*list = create_list_of_nodes(node);
	else
	{
		t_list_of_nodes *start = *list;

		while ((*list)->next != NULL)
		{
			
			check_parameters_equalness((*list)->node, node, lem);
			*list = (*list)->next;
		}
		check_parameters_equalness((*list)->node, node, lem);
	
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
		add_node_to_list(&n1->links, n2, lem);
	if (!path_contains_node(n2->links, n1))
		add_node_to_list(&n2->links, n1, lem);
}

t_list_of_nodes	*copy_list_of_nodes(t_list_of_nodes *path, t_lem *lem)
{
	// t_list_of_nodes *start = path;
	t_list_of_nodes	*new_path = NULL;
	while (path != NULL)
	{
		
		add_node_to_list(&new_path, path->node, lem);
		path = path->next;
	}
	// path = start;
	return(new_path);
}

void	delete_path(t_list_of_nodes *path)
{
	t_list_of_nodes *start = path;

	while (path->next != NULL)
	{
		while (path->next->next != NULL)
		path = path->next;
		free(path->next);
		path->next = NULL;
		path = start;
	}
	free(path);
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
			add_node_to_list(&lem->nodes, buf, lem);
			if (lem->start != NULL)
				error("Too much start rooms", lem);
			lem->start = buf;
		}
		else if (ft_strequ(line, "##end"))
		{
			
			ft_strdel(&line);
			get_next_line_counter(GNL_READ_MODE, 0, &line);
			t_node *buf = create_node(line, lem);
			add_node_to_list(&lem->nodes, buf, lem);
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
			add_node_to_list(&lem->nodes, create_node(line, lem), lem);
		ft_strdel(&line);
	}
}

void	find_pathes(t_node *end, t_list_of_nodes *tmp, t_lem *lem)
{
	t_node *start;
	t_list_of_nodes *buf;
	buf = tmp;
	while (tmp)
	{
		start = tmp->node;
		tmp = tmp->next;
	}
	tmp = buf;
	if (start == end)
	{
		add_path_to_list(&lem->pathes, tmp);
		return;
	}
	buf = start->links;
	while (start->links)
	{
		if (!path_contains_node(tmp, start->links->node)) // else going back
		{
			t_list_of_nodes *copy = copy_list_of_nodes(tmp, lem);
			add_node_to_list(&copy, start->links->node, lem);
			find_pathes(end, copy, lem);
		}
		start->links = start->links->next;
	}
	start->links = buf;
	delete_path(tmp);
}



void	swap_pathes(t_list_of_nodes **a, t_list_of_nodes **b)
{
	t_list_of_nodes *tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sort_pathes_by_length(t_list_of_pathes *list)
{
	t_list_of_pathes *tmp = list;
	int i = -1;
	while (tmp)
	{
		t_list_of_pathes *start = list;
		while (list->next)
		{

			if (path_len(list->path) > path_len(list->next->path))
				swap_pathes(&list->path, &list->next->path);
			list = list->next;

		}
		list = start;
		tmp = tmp->next;
	}
}

void	sort_pathes_by_group(t_list_of_pathes *list)
{
	t_list_of_pathes *tmp = list;
	int i = -1;
	while (tmp)
	{
		t_list_of_pathes *start = list;
		while (list->next)
		{

			if (list->path->group > list->next->path->group)
				swap_pathes(&list->path, &list->next->path);
			list = list->next;

		}
		list = start;
		tmp = tmp->next;
	}
}

int		pathes_are_connected(t_list_of_nodes *path_1, t_list_of_nodes *path_2, t_lem *lem)
{
	while (path_1)
	{
		if (path_1->node != lem->start && path_1->node != lem->end &&
			path_contains_node(path_2, path_1->node))
		return (1);
		path_1 = path_1->next;
	}
	
	return (0);
}

void	check_compatibility(t_list_of_nodes *path, t_list_of_pathes *list, t_lem *lem)
{
	while (list)
	{
		if (pathes_are_connected(path, list->path, lem))
		{
			list->path->group = path->group + 1;
			// printf("found\n");
		}
		list = list->next;
	}
}

void	split_to_groups(t_list_of_pathes *list, t_lem *lem)
{
	if (list == NULL)
		error("Not enough data to process", lem);
	while (list->next)
	{
		check_compatibility(list->path, list->next, lem);
		// show_all_pathes(lem->pathes);
		list = list->next;
	}
	
}

int		select_optimal_group(t_list_of_pathes *list, t_lem *lem)
{
	int group = -1;
	int pathes=  0;
	int total_length=  0;
	int steps;
	int min = __INT_MAX__;
	int res_value;
	while (list)
	{
		if (list->path->group != group)
		{
			if (group != -1)
			{
				steps = (lem->ants + total_length) / pathes - 1;
				if (steps < min)
				{
					min = steps;
					res_value = group;
				}
					
				printf("Group %d. Pathes: %d, steps: %d", group, pathes, steps);
				if (lem->ants > pathes && (lem->ants + total_length) % pathes != 0)
					printf(" + 1\n");
				else
					printf("\n");
			}
			group++;
			pathes = 0;
			total_length = 0;
		}
		pathes += 1;
		total_length += path_len(list->path);
		list = list->next;
	}
	steps = (lem->ants + total_length) / pathes - 1;
	if (steps < min)
	{
		min = steps;
		res_value = group;
	}
	printf("Group %d. Pathes: %d, steps: %d", group, pathes, steps);
	if (lem->ants > pathes && (lem->ants + total_length) % pathes != 0)
		printf(" + 1\n");
	else
		printf("\n");
	return (res_value);
}


int		main(void)
{
	t_lem *lem = init();
	read_map(lem);

	if (lem->start == NULL)
		error("The start room is missing", lem);
	if (lem->end == NULL)
		error("The end room is missing", lem);

	find_pathes(lem->end, create_list_of_nodes(lem->start), lem);
	show_all_pathes(lem->pathes);

	sort_pathes_by_length(lem->pathes);
	show_all_pathes(lem->pathes);

	split_to_groups(lem->pathes, lem);
	// show_all_pathes(lem->pathes);

	// sort_pathes_by_group(lem->pathes);
	// show_all_pathes(lem->pathes);

	// printf("Optimal group: %d\n", select_optimal_group(lem->pathes, lem));

	system("leaks lem-in");
	return (0);
}
