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


t_lem	*init()
{
	t_lem *lem = ft_memalloc(sizeof(t_lem));
	lem->nodes = NULL;
	lem->pathes = NULL;
	lem->start = NULL;
	lem->end = NULL;
	return (lem);
}

void	error(char *message)
{
	ft_printf("ERROR: %s\n", message);
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

// void	create_node(char *name, t_lem *lem)
// {
// 	t_node *node = ft_memalloc(sizeof(t_node));
// 	node->name = name;
// 	node->n_links = 0;
// 	// node->links = ft_memalloc(sizeof(t_node*) * num_links);
// 	// int i = -1;
// 	// while (++i < num_links)
// 	// 	node->links[i] = NULL;
// 	lem->nds[lem->n_nds++] = node;
// }

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
	while (nodes)
	{
		if (ft_strequ(name, nodes->node->name))
			return (nodes->node);
		nodes = nodes->next;
	}
	return (NULL);
}

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

void	add_node_to_list(t_list_of_nodes **list, t_node *node)
{
	if (*list == NULL)
		*list = create_list_of_nodes(node);
	else
	{
		while ((*list)->next != NULL)
			*list = (*list)->next;
		(*list)->next = ft_memalloc(sizeof(t_list_of_nodes));
		(*list)->next->node = node;
		(*list)->next->next = NULL;
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
		while ((*list)->next != NULL)
			*list = (*list)->next;
		(*list)->next = ft_memalloc(sizeof(t_list_of_pathes));
		(*list)->next->path = path;
		(*list)->next->next = NULL;
	}
}

void	create_link(t_node *node_1, t_node *node_2) // mb between nodes?
{
	if (node_1 == NULL || node_2 == NULL)
	{
		printf("Unknown node\n");
		return;
	}
	if (!path_contains_node(node_1->links, node_2))
		add_node_to_list(&node_1->links, node_2);
	if (!path_contains_node(node_2->links, node_1))
		add_node_to_list(&node_2->links, node_1);
}

t_list_of_nodes	*copy_list_of_nodes(t_list_of_nodes *path)
{
	t_list_of_nodes	*new_path = NULL;
	while (path->next != NULL)
	{
		path = path->next;
		add_node_to_list(&new_path, path->node);
	}
	return(new_path);
}

// void	delete_node(t_node *node)
// {
// 	ft_strdel(&node->name);
// 	ft_memdel((void**)&node->links);
// 	ft_memdel((void**)&node);
// }

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

void	find_pathes(t_node *end, t_list_of_nodes *tmp, t_lem *lem)
{
	t_node *start;
	t_list_of_nodes *buf = tmp;
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
			t_list_of_nodes *copy = copy_list_of_nodes(tmp);
			add_node_to_list(&copy, start->links->node);
			find_pathes(end, copy, lem);
		}
		start->links = start->links->next;
	}
	start->links = buf;
	delete_path(tmp);
}

t_node	*create_node(char *line)
{
	char *itoa1;
	char *itoa2;
	char **params = ft_strsplit(line, ' ');

	if (ft_arrlen(params) != 3)
		error("Incorrect number of a room properties");
	if (ft_char_count(' ', line) != 2)
		error("Room definition example: 'name x y'");
	if (params[0][0] == 'L')
		error("Incorrect room name");
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
		error("Room's coordinates must be integers");
	ft_strdel(&itoa1);
	ft_strdel(&itoa2);
	node->links = NULL;
	ft_arrclr(params);
	return (node);
}

void	read_map(t_lem *lem)
{
	char *line;
	
	get_next_line(0, &line);
	char *itoa = ft_itoa(ft_atoi(line));
	if (ft_strequ(itoa, line) && ft_atoi(line) > 0)
		lem->ants = ft_atoi(line);
	else
		error("Number of ants must be a positive integer");
	ft_strdel(&itoa);
	ft_strdel(&line);
	while (get_next_line(0, &line))
	{
		if (ft_strequ(line, "##start"))
		{
			ft_strdel(&line);
			get_next_line(0, &line);
			t_node *buf = create_node(line);
			add_node_to_list(&lem->nodes, buf);
			if (lem->start != NULL)
				error("Too much start rooms");
			lem->start = buf;
		}
		else if (ft_strequ(line, "##end"))
		{
			ft_strdel(&line);
			get_next_line(0, &line);
			t_node *buf = create_node(line);
			add_node_to_list(&lem->nodes, buf);
			if (lem->end != NULL)
				error("Too much start rooms");
			lem->end = buf;
		}
		// else if ()
		// {
			
		// }
		else if (line[0] == '#')
		{
			printf("%s skipped\n", line);
		}
		ft_strdel(&line);
	}
	
}

int		main(void)
{
	t_lem *lem = init();
	read_map(lem);

	// if (lem->nodes == NULL)
	// 	lem->nodes = create_list_of_nodes(create_node("A 0 0"));
	// add_node_to_list(lem->nodes, create_node("B 0 0"));
	// add_node_to_list(lem->nodes, create_node("C 0 0"));
	// add_node_to_list(lem->nodes, create_node("D 0 0"));
	// add_node_to_list(lem->nodes, create_node("E 0 0"));
	// add_node_to_list(lem->nodes, create_node("F 0 0"));
	// create_link(find_node("A", lem->nodes), find_node("B", lem->nodes));
	// create_link(find_node("A", lem->nodes), find_node("C", lem->nodes));
	// create_link(find_node("B", lem->nodes), find_node("D", lem->nodes));
	// create_link(find_node("C", lem->nodes), find_node("E", lem->nodes));
	// create_link(find_node("C", lem->nodes), find_node("D", lem->nodes));
	// create_link(find_node("F", lem->nodes), find_node("E", lem->nodes));
	// create_link(find_node("D", lem->nodes), find_node("F", lem->nodes));
	// create_link(find_node("D", lem->nodes), find_node("F", lem->nodes));
	// t_node *end = find_node("F", lem->nodes);
	// t_list_of_nodes *tmp = create_list_of_nodes(find_node("A", lem->nodes));
	// show_all_nodes(lem->nodes, lem);
	// find_pathes(end, tmp, lem);
	// show_all_pathes(lem->pathes);

	show_all_nodes(lem->nodes, lem);

	system("leaks lem-in");
	return (0);
}
