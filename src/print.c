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

int		is_directly(t_list_of_nodes *path, t_lem *lem)
{
	if (path->node == lem->start && path->next->node == lem->end)
		return (1);
	else
		return (0);
}

void	new_ants(t_list_of_ants **ants, t_list_of_pathes *pathes, int *ant_counter, t_lem *lem)
{

	t_list_of_pathes *start = pathes;
	while (pathes && lem->ants - *ant_counter != 0)
	{
		if (is_directly(start->path, lem))
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

void	show_steps(t_list_of_ants *ants, t_lem *lem)
{
	while (ants)
	{
		// char *color = DEFAULT;
		if (lem->flag_color)
		{
			if (ants->ant_id % 6 == 0)
				ft_putstr(RED);
			else if (ants->ant_id % 6 == 1)
				ft_putstr(GREEN);
			else if (ants->ant_id % 6 == 2)
				ft_putstr(YELLOW);
			else if (ants->ant_id % 6 == 3)
				ft_putstr(BLUE);
			else if (ants->ant_id % 6 == 4)
				ft_putstr(PURPLE);
			else if (ants->ant_id % 6 == 5)
				ft_putstr(CYAN);
			if (ants->position->node->marked)
				ft_putstr(BG_RED);
		}
		ft_printf("L%d-%s", ants->ant_id,
			ants->position->node->name);
		if (lem->flag_color)
			ft_putstr(DEFAULT);
		ft_putchar(' ');
		ants = ants->next;
	}
	ft_putchar('\n');
}

void	print_path(t_list_of_nodes *path)
{
	while (1)
	{
		if (path->node->marked)
			ft_putstr(BG_RED);
		ft_putstr(path->node->name);
		if (path->node->marked)
			ft_putstr(BG_DEFAULT);
		if (path->next == NULL)
			break;
		else
		{
			ft_putstr("->");
		}
		path = path->next;
	}
	ft_putchar('\n');
}

void	show_pathes(t_list_of_pathes *list, t_lem *lem)
{
	int count = 0;

	if (lem->flag_color)
		ft_putstr(RED);
	printf("\nUnique pathes:\n");
	
	t_list_of_pathes *start = list;
	while (list)
	{
		if (lem->flag_color)
		{
			if (++count % 2 == 0)
				ft_putstr(BLUE);
			else
				ft_putstr(YELLOW);
		}
		print_path(list->path);

		// ft_strdel(&path);
		list = list->next;
	}
	ft_putstr(DEFAULT);
	list = start;
	
}

void	print_total_steps(int total, t_lem *lem)
{
	if (lem->flag_color)
		ft_putstr(RED);
		ft_printf("\nTolal steps: %d\n", total);
	if (lem->flag_color)
		ft_putstr(DEFAULT);
}

void	directly(t_lem *lem)
{
	int i = 0;
	while (++i <= lem->ants)
	{

	}
}


void	print_steps(t_list_of_pathes *pathes, t_lem *lem)
{
	t_list_of_ants *ants = NULL;

	int ant_counter = 0;
	int total = 0;

	// if (pathes->path->node == lem->start && pathes->path->next->node == lem->end)
	// {
	// 	directly();
	// }
	// else
	// {
		new_ants(&ants, pathes, &ant_counter, lem);
		while (ants)
		{
			step(ants, lem);
			show_steps(ants, lem);
			remove_finishers(&ants, lem);
			new_ants(&ants, pathes, &ant_counter, lem);
			total++;
		}
		delete_list_of_ants(ants); // need ?
	// }
	
	if (lem->flag_pathes)
		show_pathes(pathes, lem);
	if (lem->flag_steps)
		print_total_steps(total, lem);
	
}
