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

int		arrlen(char **arr)
{
	int i = 0;
	if (arr == NULL)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

int		space_count(char *line)
{
	int i = -1;
	int res = 0;
	while (line[++i])
	{
		if (line[i] == ' ')
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

void	add_node_to_list(t_list_of_nodes *list, t_node *node)
{
	while (list->next != NULL)
		list = list->next;
	list->next = ft_memalloc(sizeof(t_list_of_nodes));
	list->next->node = node;
	list->next->next = NULL;
}

void	add_path_to_list(t_list_of_pathes *list, t_list_of_nodes *path)
{
	while (list->next != NULL)
		list = list->next;
	list->next = ft_memalloc(sizeof(t_list_of_pathes));
	list->next->path = path;
	list->next->next = NULL;
}

void	create_link(char *name1, char *name2, t_lem *lem)
{
	t_node *n1 = find_node(name1, lem->nodes);
	t_node *n2 = find_node(name2, lem->nodes);

	if (n1 == NULL)
	{
		printf("Unknown node: %s\n", name1);
		return;
	}
	if (n2 == NULL)
	{
		printf("Unknown node: %s\n", name2);
		return;
	}
	if (n1->links == NULL)
		n1->links = create_list_of_nodes(n2);
	else if (!path_contains_node(n1->links, n2))
		add_node_to_list(n1->links, n2);
	if (n2->links == NULL)
		n2->links = create_list_of_nodes(n1);
	else if (!path_contains_node(n2->links, n1))
		add_node_to_list(n2->links, n1);
}

t_list_of_nodes	*copy_path(t_list_of_nodes *path)
{
	t_list_of_nodes	*new_path = create_list_of_nodes(path->node);
	while (path->next != NULL)
	{
		path = path->next;
		add_node_to_list(new_path, path->node);
	}
	return(new_path);
}

void	delete_node(t_node *node)
{
	ft_strdel(&node->name);
	ft_memdel((void**)&node->links);
	ft_memdel((void**)&node);
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

// void	find_pathes(t_node *start, t_node *end, t_list_of_nodes *tmp, t_lem *lem)
// {
// 	if (start == end)
// 	{
// 		// lem->pts[lem->n_pts++] = tmp;
// 		if (lem->pathes == NULL)
// 			lem->pathes = create_list_of_pathes(tmp);
// 		else
// 			add_path_to_list(lem->pathes, tmp);
// 		return;
// 	}
// 	int i = -1;
// 	while (++i < start->n_links)
// 	{
// 		if (start->links[i] == NULL)
// 		{
// 			printf("Something wrong with %s links\n", start->name);
// 			return;
// 		}
// 		if (!path_contains(tmp, start->links[i])) // else going back
// 		{
// 			t_list_of_nodes *list = copy_path(tmp);
// 			// add_to_path(list, start->links[i]);
// 			find_pathes(start->links[i], end, list, lem);
// 		}
// 	}
// 	delete_path(tmp);
// }

t_node	*create_node(char *line)
{

	char **params = ft_strsplit(line, ' ');
	if (arrlen(params) != 3)
		error("Incorrect number of a room properties");
	if (space_count(line) != 2)
		error("Too many spaces defining a room");
	if (params[0][0] == 'L')
		error("Incorrect room name");
	t_node	*node = ft_memalloc(sizeof(t_node));
	node->name = ft_strdup(params[0]);
	node->x = ft_atoi(params[1]);
	node->y = ft_atoi(params[2]);
	node->links = NULL;
	ft_arrclr(params);
	return (node);
	
}

void	read_map(t_lem *lem)
{
	char *line;
	
	get_next_line(0, &line);
	if (ft_atoi(line) > 0)
		lem->ants = ft_atoi(line);
	else
		error("Incorrect number of ants");
	ft_strdel(&line);
	while (get_next_line(0, &line))
	{
		if (ft_strequ(line, "##start"))
		{
			ft_strdel(&line);
			get_next_line(0, &line);
			t_node *buf = create_node(line);
			if (lem->start != NULL)
				error("Too much start rooms");
			lem->start = buf;
		}
		else if (ft_strequ(line, "##end"))
		{
			ft_strdel(&line);
			get_next_line(0, &line);
			t_node *buf = create_node(line);
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
	// read_map(lem);

	t_node *a = create_node("A 0 0");
	t_node *b = create_node("B 0 0");

	if (lem->nodes == NULL)
		lem->nodes = create_list_of_nodes(a);
	add_node_to_list(lem->nodes, b);
	add_node_to_list(lem->nodes, create_node("C 0 0"));
	add_node_to_list(lem->nodes, create_node("D 0 0"));
	add_node_to_list(lem->nodes, create_node("E 0 0"));
	add_node_to_list(lem->nodes, create_node("F 0 0"));

	// create_link("hello", "F", lem);
	// a->links = create_list_of_nodes(b);

	create_link("A", "F", lem);
	create_link("B", "D", lem);
	create_link("C", "E", lem);
	create_link("C", "D", lem);
	create_link("F", "E", lem);
	create_link("D", "F", lem);
	create_link("D", "F", lem);

	show_all_nodes(lem->nodes, lem);
	show_all_nodes(lem->nodes, lem);

	// t_node *start = find_node("A", lem->nodes);
	// t_node *end = find_node("F", lem->nodes);


	// t_list_of_nodes *path = create_list_of_nodes(start);
	// t_list_of_nodes *path_end = create_list_of_nodes(end);
	// add_node_to_list(path, find_node("B", lem->nodes));

	// if (lem->pathes == NULL)
	// 	lem->pathes = create_list_of_pathes(path);
	// add_path_to_list(lem->pathes, path_end);


	// show_all_pathes(lem->pathes);
	// show_all_pathes(lem->pathes);

	// find_pathes(start, end, path, lem);


	// system("leaks lem-in");
	return (0);
}
