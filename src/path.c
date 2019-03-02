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

#include "lem-in.h"

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