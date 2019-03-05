/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 15:31:49 by osamoile          #+#    #+#             */
/*   Updated: 2018/08/24 15:31:50 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void					delete_path(t_list_of_nodes *path)
{
	t_list_of_nodes *start;

	start = path;
	if (path == NULL)
		return ;
	while ((path)->next != NULL)
	{
		while ((path)->next->next != NULL)
			path = (path)->next;
		free((path)->next);
		(path)->next = NULL;
		path = start;
	}
	free(path);
}

static t_list_of_pathes	*create_list_of_pathes(t_list_of_nodes *first_path)
{
	t_list_of_pathes *list;

	list = ft_memalloc(sizeof(t_list_of_pathes));
	list->path = first_path;
	list->next = NULL;
	return (list);
}

void					push_path(t_list_of_pathes **list,
						t_list_of_nodes *path)
{
	t_list_of_pathes *start;

	if (*list == NULL)
		*list = create_list_of_pathes(path);
	else
	{
		start = *list;
		while ((*list)->next != NULL)
			*list = (*list)->next;
		(*list)->next = ft_memalloc(sizeof(t_list_of_pathes));
		(*list)->next->path = path;
		(*list)->next->next = NULL;
		*list = start;
	}
}

int						path_len(t_list_of_nodes *list)
{
	int i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i - 1);
}
