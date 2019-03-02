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

#include "lem-in.h"

void	delete_list_of_ants(t_list_of_ants *ants)
{
	t_list_of_ants *start = ants; // ?
	if (ants == NULL)
		return;
	while ((ants)->next != NULL)
	{
		while ((ants)->next->next != NULL)
			ants = (ants)->next;
		free((ants)->next);
		(ants)->next = NULL;
		ants = start;
	}
	free(ants);
	// path = NULL;
	
}


t_list_of_ants	*create_list_of_ants(int num, t_list_of_nodes *ant_position)
{
	t_list_of_ants *ants = ft_memalloc(sizeof(t_list_of_ants));
	ants->ant_id = num;
	ants->position = ant_position;
	ants->next = NULL;
	return (ants);
}

void	push_ant(t_list_of_ants **ants, int num, t_list_of_nodes *ant_position, t_lem *lem)
{
	if (*ants == NULL)
		*ants = create_list_of_ants(num, ant_position);
	else
	{
		t_list_of_ants *start = *ants;

		while ((*ants)->next != NULL)
		{
			
			// check_parameters_equalness((*list)->node, node, lem);
			*ants = (*ants)->next;
		}
		// check_parameters_equalness((*list)->node, node, lem);
	
		(*ants)->next = ft_memalloc(sizeof(t_list_of_ants));
		(*ants)->next->ant_id = num;
		(*ants)->next->position = ant_position;
		(*ants)->next->next = NULL;
		*ants = start; // fix
	}
}