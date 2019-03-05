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

#include "lemin.h"

int			get_next_line_counter(int mode, int fd, char **line, t_lem *lem)
{
	static int	count = 0;
	int			res;

	if (mode == GNL_READ_MODE)
	{
		count++;
		res = get_next_line(fd, line);
		if (lem->flag_color)
			ft_putstr(RED);
		if (res)
			ft_putendl(*line);
		if (lem->flag_color)
			ft_putstr(DEFAULT);
		return (res);
	}
	else if (mode == GNL_RETURN_COUNT_MODE)
		return (count);
	else
		return (0);
}

static int	command(char *line)
{
	if (ft_strequ(line, "##start") ||
	ft_strequ(line, "##end") ||
	ft_strequ(line, "##mark"))
		return (1);
	else
		return (0);
}

static void	ants_mode(char *line, int *mode, t_lem *lem)
{
	char *itoa;

	if (command(line))
		error("Commands are forbidden befone number of ants", lem);
	else
	{
		itoa = ft_itoa(ft_atoi(line));
		if (ft_strequ(itoa, line) && ft_atoi(line) > 0)
			lem->ants = ft_atoi(line);
		else
			error("Number of ants must be a positive integer", lem);
		ft_strdel(&itoa);
		*mode = MAP_ROOMS_MODE;
	}
}

void		links_mode(char *line, t_lem *lem)
{
	if (command(line))
		error("Commands are forbidden for links", lem);
	else
		create_link(line, lem);
}

void		read_map(t_lem *lem)
{
	char	*line;
	int		mode;

	mode = MAP_ANTS_MODE;
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
	ft_putchar('\n');
}
