/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
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
		t_list_of_pathes *tmp = start;
		int shorter_ways_sum = 0;
		while (tmp != pathes)
		{
			shorter_ways_sum += path_len(pathes->path) - path_len(tmp->path);
			tmp = tmp->next;
		}

		// printf("ants: %d\n", lem->ants - *ant_counter);
		if (lem->ants - *ant_counter > shorter_ways_sum)
		{
			
			(*ant_counter)++;

			// printf("\t%d choose ", *ant_counter); show_path(pathes->path);

			push_ant(ants, *ant_counter, pathes->path, lem);


		}
		pathes = pathes->next;
		
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

void	show_steps(t_list_of_ants *ants)
{
	while (ants)
	{
		char *color = DEFAULT;
		if (ants->ant_id % 5 == 0)
			printf(RED);
		else if (ants->ant_id % 5 == 1)
			printf(GREEN);
		else if (ants->ant_id % 5 == 2)
			printf(CYAN);
		else if (ants->ant_id % 5 == 3)
			printf(YELLOW);
		else if (ants->ant_id % 5 == 4)
			printf(PURPLE);

		printf("L%d-%s ", ants->ant_id,
			ants->position->node->name);

			printf("%s", DEFAULT);
		ants = ants->next;
	}
	printf("\n");
}


void	print_steps(t_list_of_pathes *pathes, t_lem *lem)
{
	t_list_of_ants *ants = NULL;

	int ant_counter = 0;

	new_ants(&ants, pathes, &ant_counter, lem);
	while (ants)
	{
		step(ants, lem);

		show_steps(ants);

		remove_finishers(&ants, lem);
		new_ants(&ants, pathes, &ant_counter, lem);
	}
	delete_list_of_ants(ants); // need ?
}
