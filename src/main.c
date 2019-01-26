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

t_node	*create_node(char *name, int num_links)
{
	t_node *node = ft_memalloc(sizeof(t_node));
	node->name = name;
	node->num_links = num_links;
	node->links = ft_memalloc(sizeof(t_node*) * num_links);
	int i = -1;
	while (++i < num_links)
		node->links[i] = NULL;
	return (node);
}

void	create_link(t_node *n1, t_node *n2)
{
	int i = 0;
	while (n1->links[i] != NULL)
	{
		i++;
		if (i == n1->num_links)
		{
			printf("%s: slots - %d, link number - %d\n", n1->name, n1->num_links, i + 1);
			return;
		}
	}
	n1->links[i] = n2;

	i = 0;
	while (n2->links[i] != NULL)
	{
		i++;
		if (i == n2->num_links)
		{
			printf("%s: slots - %d, link number - %d\n", n2->name, n2->num_links, i + 1);
			return;
		}
	}
	n2->links[i] = n1;
}

void	show_node(t_node *n)
{
	printf("%s, %d links:\n", n->name, n->num_links);
	int i = -1;
	while (++i < n->num_links)
	{
		if (n->links[i] != NULL)
			printf("\t%s\n", n->links[i]->name);
		else
			printf("\tEmpty link\n");
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

void	find_pathes(t_node *start, t_node *end, t_path *tmp)
{
	if (start == end)
	{
		show_path(tmp);
		delete_path(tmp);
		return;
	}
	int i = -1;
	while (++i < start->num_links)
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
			find_pathes(start->links[i], end, p);
		}
	}
	delete_path(tmp);
}

int		main(void)
{
	t_node *A = create_node("A", 3);
	t_node *B = create_node("B", 2);
	t_node *C = create_node("C", 3);
	t_node *D = create_node("D", 3);
	t_node *E = create_node("E", 2);
	t_node *F = create_node("F", 2);
	t_node *K = create_node("K", 2);
	t_node *M = create_node("M", 2);

	create_link(A, B);
	create_link(A, C);
	create_link(A, F);
	create_link(B, K);
	create_link(C, D);
	create_link(C, M);
	create_link(K, D);
	create_link(M, E);
	create_link(E, F);
	create_link(D, F);


	// t_path *second_path = copy_path(path);
	// show_path(path);
	// show_path(second_path);

	// printf("%d\n", path_contains(path, E));

	t_path *path = create_path(A);
	find_pathes(A, F, path);
	// system("leaks lem-in");



	return (0);
}
