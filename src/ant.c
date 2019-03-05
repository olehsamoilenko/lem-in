/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 15:31:49 by osamoile          #+#    #+#             */
/*   Updated: 2018/08/24 15:31:50 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_list_of_ants	*create_list_of_ants(int num,
						t_list_of_nodes *ant_position)
{
	t_list_of_ants *ants;

	ants = ft_memalloc(sizeof(t_list_of_ants));
	ants->ant_id = num;
	ants->position = ant_position;
	ants->next = NULL;
	return (ants);
}

void					remove_ant(t_list_of_ants **ants, t_list_of_ants *ant)
{
	t_list_of_ants *tmp;
	t_list_of_ants *start;

	tmp = NULL;
	if (*ants == ant)
	{
		tmp = *ants;
		*ants = (*ants)->next;
	}
	else
	{
		start = *ants;
		while (start->next)
		{
			if (start->next == ant)
			{
				tmp = start->next;
				start->next = start->next->next;
				break ;
			}
			start = start->next;
		}
	}
	free(tmp);
}

void					push_ant(t_list_of_ants **ants, int num,
						t_list_of_nodes *ant_position)
{
	t_list_of_ants *start;

	if (*ants == NULL)
		*ants = create_list_of_ants(num, ant_position);
	else
	{
		start = *ants;
		while (start->next != NULL)
			start = start->next;
		start->next = ft_memalloc(sizeof(t_list_of_ants));
		start->next->ant_id = num;
		start->next->position = ant_position;
		start->next->next = NULL;
	}
}
