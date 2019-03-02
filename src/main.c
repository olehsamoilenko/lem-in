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
	lem->flag_color = 0;
	return (lem);
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



void	show_all_ants(t_list_of_ants *ants)
{
	while (ants)
	{
		printf("id: %d\tposition: %s\n", ants->ant_id, ants->position->node->name);
		ants = ants->next;
	}
	printf("\n");
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

void	print_usage()
{
	printf("Usage: ./lem-in [-c] < map\n");
	exit(0);
}

void	flags_handle(int argc, char **argv, t_lem *lem)
{
	int i = 0;
	while (++i < argc)
	{
		if (ft_strequ(argv[i], "-c"))
		{
			lem->flag_color = 1;
		}
		else
		{
			print_usage();
		}
			
	}
}



int		main(int argc, char **argv)
{
	t_lem *lem = init();
	flags_handle(argc, argv, lem);
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
	
	// show_all_nodes(lem->nodes, lem);
	
	reset_used_nodes(lem->nodes, lem);
	sort_nodes_by_amount_of_links(lem->nodes, lem);

	// show_all_nodes(lem->nodes, lem);

	while ((path = bfs_less_links_oriented(lem->end, lem->start, lem)))
		push_path(&lem->pathes_2, path);
	sort_list(lem->pathes_2);
	show_all_pathes(lem->pathes_2, lem);




	if (!lem->pathes_1 && !lem->pathes_2)
		error("Not enough data to process", lem);
	
	t_list_of_pathes *pathes;
	if (total_steps(lem->pathes_1, lem) <= total_steps(lem->pathes_2, lem))
		pathes = lem->pathes_1;
	else
		pathes = lem->pathes_2;

	show_all_pathes(pathes, lem);

	print_steps(pathes, lem);

	
	system("leaks lem-in");
	return (0);
}
