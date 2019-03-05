/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_contribution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 15:31:49 by osamoile          #+#    #+#             */
/*   Updated: 2018/08/24 15:31:50 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	step(t_list_of_ants *ants, t_lem *lem)
{
	t_list_of_ants *buf = ants;
	while (buf)
	{
		buf->position = buf->position->next;
		buf = buf->next;
	}
}

void	new_ants(t_list_of_ants **ants, t_list_of_pathes *pathes, int *ant_counter, t_lem *lem)
{
	t_list_of_pathes *start = pathes;
	while (pathes && lem->ants - *ant_counter != 0)
	{
		if (start->path->node == lem->start && start->path->next->node == lem->end)
		{
			(*ant_counter)++;
			push_ant(ants, *ant_counter, pathes->path, lem);
		}
		else
		{
			t_list_of_pathes *tmp = start;
			int shorter_ways_sum = 0;
			while (tmp != pathes)
			{
				shorter_ways_sum += path_len(pathes->path) - path_len(tmp->path);
				tmp = tmp->next;
			}
			if (lem->ants - *ant_counter > shorter_ways_sum)
			{
				(*ant_counter)++;
				push_ant(ants, *ant_counter, pathes->path, lem);
			}
			pathes = pathes->next;
		}
	}
	pathes = start;
}


void	remove_ant(t_list_of_ants **ants, t_list_of_ants *ant)
{
	t_list_of_ants *tmp;
	
	if (*ants == ant)
	{
		tmp = *ants;
		*ants = (*ants)->next;
	}
	else
	{
		t_list_of_ants *start = *ants;
		while ((*ants)->next)
		{
			if ((*ants)->next == ant)
			{
				tmp = (*ants)->next;
				(*ants)->next = (*ants)->next->next;
				break;
			}
			*ants = (*ants)->next;
		}
		*ants = start;
	}
	free(tmp);
}

void	remove_finishers(t_list_of_ants **ants, t_lem *lem)
{
	t_list_of_ants *tmp = *ants;
	while (tmp)
	{
		if (tmp->position->node == lem->end)
			remove_ant(ants, tmp);
		tmp = tmp->next;
	}
}

void	ants_contribution(t_list_of_pathes *pathes, t_lem *lem)
{
	t_list_of_ants *ants;
	int ant_counter;
	int total;

	ants = NULL;
	ant_counter = 0;
	total = 0;
	new_ants(&ants, pathes, &ant_counter, lem);
	while (ants)
	{
		step(ants, lem);
		print_steps(ants, lem);
		remove_finishers(&ants, lem);
		new_ants(&ants, pathes, &ant_counter, lem);
		total++;
	}
	if (lem->flag_pathes)
		print_pathes(pathes, lem);
	if (lem->flag_steps)
		print_total_steps(total, lem);
}
