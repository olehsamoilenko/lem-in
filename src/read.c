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

static void	read_number_of_ants(char *line, t_lem *lem)
{
	while(get_next_line_counter(GNL_READ_MODE, 0, &line) && line[0] == '#')
	{
		if (ft_strequ(line, "##start"))
			error("There is start command before number of ants", lem);
			
		if (ft_strequ(line, "##end"))
			error("There is end command before number of ants", lem);

		ft_strdel(&line);
	}
	if (!line)
		error("Number of ants is missing", lem);
	char *itoa = ft_itoa(ft_atoi(line));
	if (ft_strequ(itoa, line) && ft_atoi(line) > 0)
		lem->ants = ft_atoi(line);
	else
		error("Number of ants must be a positive integer", lem);
	ft_strdel(&itoa);
	ft_strdel(&line);
}

int		name_is_unique(t_node *node, t_list_of_nodes *nodes)
{
	while (nodes)
	{
		if (ft_strequ(nodes->node->name, node->name))
			return (0);
		nodes = nodes->next;
	}
	return (1);
}

void	push_unique_room(t_node *node, t_lem *lem)
{
	if (name_is_unique(node, lem->nodes))
		push_node(&lem->nodes, node, lem);
	else
		error("Room's name must be unique", lem);
}

void	handle_start_room(t_lem *lem)
{
	char *line;

	// ft_strdel(&line);
	get_next_line_counter(GNL_READ_MODE, 0, &line);
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

	get_next_line_counter(GNL_READ_MODE, 0, &line);
	t_node *node = create_node(line, lem);
	ft_strdel(&line);
	push_unique_room(node, lem);
	if (lem->end != NULL)
		error("Too much end rooms", lem);
	lem->end = node;
}

int		line_is_link(char *line)
{
	if(ft_strchr(line, '-') && ft_char_count(' ', line) == 0)
		return (1);
	else
		return (0);

}

void	read_map(t_lem *lem)
{
	char *line;
	int mode = MAP_ROOMS_MODE;
	
	read_number_of_ants(line, lem);
	while (get_next_line_counter(GNL_READ_MODE, 0, &line))
	{
		if (ft_strequ(line, "##start"))
			handle_start_room(lem);
		else if (ft_strequ(line, "##end"))
			handle_end_room(lem);
		else if (line[0] == '#')
			;
		else if (mode == MAP_LINKS_MODE || line_is_link(line))
		{
			create_link(line, lem);
			mode = MAP_LINKS_MODE;
		}
		else if (mode == MAP_ROOMS_MODE)
		{
			t_node *node = create_node(line, lem);
			push_unique_room(node, lem);
		}
		ft_strdel(&line);
	}
}