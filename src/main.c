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

int		path_contains(t_path *path, t_node *node)
{
	while (path != NULL)
	{
		if (path->node == node)
			return (1);
		path = path->next;
	}
	return (0);
}

t_node	*find_node(char *name, t_node **array, int arr_len)
{
	int i = -1;
	while (++i < arr_len)
	{
		if (ft_strequ(name, array[i]->name))
			return (array[i]);
	}
	return (NULL);
}

void	create_link(char *name1, char *name2, t_lem *lem)
{
	t_node *n1 = find_node(name1, lem->nds, lem->n_nds);
	t_node *n2 = find_node(name2, lem->nds, lem->n_nds);

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
	// int i = 0;
	// while (n1->links[i] != NULL)
	// {
	// 	i++;
	// 	if (i == n1->num_links)
	// 	{
	// 		printf("%s: number of slots - %d, link number - %d\n", n1->name, n1->num_links, i + 1);
	// 		return;
	// 	}
	// }
	n1->links[n1->n_links++] = n2;

	// i = 0;
	// while (n2->links[i] != NULL)
	// {
	// 	i++;
	// 	if (i == n2->num_links)
	// 	{
	// 		printf("%s: number of slots - %d, link number - %d\n", n2->name, n2->num_links, i + 1);
	// 		return;
	// 	}
	// }
	n2->links[n2->n_links++] = n1;
}

void	show_nodes(t_lem *lem)
{
	int i = -1;
	while (++i < lem->n_nds)
	{
		printf("%s, (%d,%d) %d links:\n", lem->nds[i]->name,
		lem->nds[i]->x, lem->nds[i]->y,
		lem->nds[i]->n_links);
		int j = -1;
		while (++j < lem->nds[i]->n_links)
		{
			if (lem->nds[i]->links[j] != NULL)
				printf("\t%s\n", lem->nds[i]->links[j]->name);
			else
				printf("\tEmpty link\n");
		}
	}
}

void	show_path(t_path *path)
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

t_path	*create_path(t_node *first_node)
{
	t_path *path = ft_memalloc(sizeof(t_path));
	path->node = first_node;
	path->next = NULL;
	return (path);
}

void	add_to_path(t_path *path, t_node *new_node)
{
	while (path->next != NULL)
		path = path->next;
	path->next = ft_memalloc(sizeof(t_path));
	path->next->node = new_node;
	path->next->next = NULL;
}

t_path	*copy_path(t_path *path)
{
	t_path	*new_path = create_path(path->node);
	while (path->next != NULL)
	{
		path = path->next;
		add_to_path(new_path, path->node);
	}
	return(new_path);
}



void	delete_node(t_node *node)
{
	ft_strdel(&node->name);
	ft_memdel((void**)&node->links);
	ft_memdel((void**)&node);
}

void	delete_path(t_path *path)
{
	t_path *start = path;

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

void	find_pathes(t_node *start, t_node *end, t_path *tmp, t_lem *lem)
{
	if (start == end)
	{
		lem->pts[lem->n_pts++] = tmp;
		return;
	}
	int i = -1;
	while (++i < start->n_links)
	{
		if (start->links[i] == NULL)
		{
			printf("Something wrong with %s links\n", start->name);
			return;
		}
		if (!path_contains(tmp, start->links[i])) // else going back
		{
			t_path *p = copy_path(tmp);
			add_to_path(p, start->links[i]);
			find_pathes(start->links[i], end, p, lem);
		}
	}
	delete_path(tmp);
}

t_lem	*init()
{
	t_lem *lem = ft_memalloc(sizeof(t_lem));
	lem->n_nds = 0;
	lem->n_pts = 0;
	lem->start = NULL;
	lem->end = NULL;
	return (lem);
}

void	error(char *message)
{
	ft_printf("ERROR: %s\n", message);
	exit(0);
}

int		arrlen(char **arr)
{
	int i = 0;
	while (arr[i])
	{
		i++;
	}
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

t_node	*create_node(char *line, t_lem *lem)
{

	char **params = ft_strsplit(line, ' ');
	if (arrlen(params) != 3)
	{
		error("Incorrect number of a room properties");
	}
	if (space_count(line) != 2)
		error("Too many spaces defining a room");
	if (params[0][0] == 'L')
		error("Incorrect room name");
	t_node	*room = ft_memalloc(sizeof(t_node));
	room->name = ft_strdup(params[0]);
	room->x = ft_atoi(params[1]);
	room->y = ft_atoi(params[2]);
	room->n_links = 0;
	lem->nds[lem->n_nds++] = room;
	ft_arrclr(params);
	return (room);
	
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
		if (ft_strstr(line, "##start") != NULL)
		{
			ft_strdel(&line);
			get_next_line(0, &line);
			t_node *buf = create_node(line, lem);
			if (lem->start != NULL)
				error("Too much start rooms");
			lem->start = buf;
			
		}
		ft_strdel(&line);
	}
	
}

int		main(void)
{
	t_lem *lem = init();
	read_map(lem);

	// create_node("A", lem);
	// create_node("B", lem);
	// create_node("C", lem);
	// create_node("D", lem);
	// create_node("E", lem);
	// create_node("F", lem);

	// create_link("hello", "F", lem);
	// create_link("A", "C", lem);
	// create_link("A", "F", lem);
	// create_link("B", "D", lem);
	// create_link("C", "E", lem);
	// create_link("C", "D", lem);
	// create_link("F", "E", lem);
	// create_link("D", "F", lem);

	show_nodes(lem);

	// t_node *start = find_node("A", lem->nds, lem->n_nds);
	// t_node *end = find_node("F", lem->nds, lem->n_nds);
	// t_path *path = create_path(start);
	// find_pathes(start, end, path, lem);

	// int i = -1;
	// while (++i < lem->n_pts)
	// 	show_path(lem->pts[i]);

	system("leaks lem-in");
	return (0);
}
