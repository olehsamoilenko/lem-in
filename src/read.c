/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 15:31:49 by osamoile          #+#    #+#             */
/*   Updated: 2018/08/24 15:31:50 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	push_unique_room(t_node *node, t_lem *lem)
{
	int unique = 1;
	t_list_of_nodes *tmp = lem->nodes;
	while (tmp)
	{
		if (ft_strequ(tmp->node->name, node->name))
			unique = 0;
		tmp = tmp->next;
	}
	if (unique)
		push_node(&lem->nodes, node, lem);
	else
		error("Room's name must be unique", lem);
}

void	handle_start_room(t_lem *lem)
{
	char *line;

	get_next_line_counter(GNL_READ_MODE, 0, &line, lem);
	t_node *node = create_node(line, lem);
	ft_strdel(&line);
	
	push_unique_room(node, lem);


	if (lem->start != NULL)
		error("Too much start rooms", lem);
	lem->start = node;
}

void	handle_end_room(t_lem *lem)
{
	char *line;

	get_next_line_counter(GNL_READ_MODE, 0, &line, lem);
	t_node *node = create_node(line, lem);
	ft_strdel(&line);
	push_unique_room(node, lem);
	if (lem->end != NULL)
		error("Too much end rooms", lem);
	lem->end = node;
}

void	handle_mark(t_lem *lem)
{
	char *line;

	get_next_line_counter(GNL_READ_MODE, 0, &line, lem);
	t_node *node = create_node(line, lem);
	ft_strdel(&line);
	push_unique_room(node, lem);
	node->marked = 1;
}

int		command(char *line)
{
	if (ft_strequ(line, "##start") ||
	ft_strequ(line, "##end") ||
	ft_strequ(line, "##mark"))
		return (1);
	else
	{
		return (0);
	}
	
}

static void	ants_mode(char *line, int *mode, t_lem *lem)
{
	if (command(line))
		error("Commands are forbidden befone number of ants", lem);
	else
	{
		char *itoa = ft_itoa(ft_atoi(line));
		if (ft_strequ(itoa, line) && ft_atoi(line) > 0)
			lem->ants = ft_atoi(line);
		else
			error("Number of ants must be a positive integer", lem);
		ft_strdel(&itoa);
		*mode = MAP_ROOMS_MODE;
	}
}

void	links_mode(char *line, t_lem *lem)
{
	if (command(line))
		error("Commands are forbidden for links", lem);
	else
		create_link(line, lem);
}

void	rooms_mode(char *line, int *mode, t_lem *lem)
{
	if (ft_strequ(line, "##start"))
		handle_start_room(lem);
	else if (ft_strequ(line, "##end"))
		handle_end_room(lem);
	else if (ft_strequ(line, "##mark"))
		handle_mark(lem);
	else if (ft_strchr(line, '-') && ft_char_count(' ', line) == 0)
	{
		*mode = MAP_LINKS_MODE;
		links_mode(line, lem);
	}
	else
	{
		t_node *node = create_node(line, lem);
		push_unique_room(node, lem);
	}
}

void	read_map(t_lem *lem)
{
	char *line;
	int mode = MAP_ANTS_MODE;

	while (get_next_line_counter(GNL_READ_MODE, 0, &line, lem))
	{
		if (ft_strequ(line, ""))
			error("Empty lines are forbidden", lem);
		else if (!command(line) && line[0] == '#')
			;
		else if (mode == MAP_ANTS_MODE)
			ants_mode(line, &mode, lem);
		else if (mode == MAP_ROOMS_MODE)
			rooms_mode(line, &mode, lem);
		else if (mode == MAP_LINKS_MODE)
			links_mode(line, lem);
		ft_strdel(&line);
	}
}