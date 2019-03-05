/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rooms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 15:31:49 by osamoile          #+#    #+#             */
/*   Updated: 2018/08/24 15:31:50 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	handle_start_room(t_lem *lem)
{
	char *line;

	get_next_line_counter(GNL_READ_MODE, 0, &line, lem);
	t_node *node = create_node(line, lem);
	ft_strdel(&line);
	
	if (!push_node(&lem->nodes, node))
		error("Room's name must be unique", lem);


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
	if(!push_node(&lem->nodes, node))
		error("Room's name must be unique", lem);
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
	if(!push_node(&lem->nodes, node))
		error("Room's name must be unique", lem);
	node->marked = 1;
}

int		line_is_link(char *line)
{
	if(ft_strchr(line, '-') && ft_char_count(' ', line) == 0)
		return (1);
	else
		return (0);
}

void	rooms_mode(char *line, int *mode, t_lem *lem)
{
	if (ft_strequ(line, "##start"))
		handle_start_room(lem);
	else if (ft_strequ(line, "##end"))
		handle_end_room(lem);
	else if (ft_strequ(line, "##mark"))
		handle_mark(lem);
	else if (line_is_link(line))
	{
		*mode = MAP_LINKS_MODE;
		links_mode(line, lem);
	}
	else
	{
		t_node *node = create_node(line, lem);
		if (!push_node(&lem->nodes, node))
			error("Room's name must be unique", lem);
	}
}
