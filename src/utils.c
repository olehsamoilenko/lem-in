/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 15:31:49 by osamoile          #+#    #+#             */
/*   Updated: 2018/08/24 15:31:50 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		get_next_line_counter(int mode, int fd, char **line, t_lem *lem)
{
	static int count = 0;
	if (mode == GNL_READ_MODE)
	{
		count++;
		int res = get_next_line(fd, line);
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
	else return (0);
}




void	error(char *message, t_lem *lem)
{
	char *line;

	char *color;
	if (lem->flag_color)
		color = RED;
	else
		color = DEFAULT;
	while (get_next_line(0, &line))
	{
		printf("%s%s%s\n", color, line, DEFAULT);
		ft_strdel(&line);
	}
	printf("\n%sERROR line %d: %s%s\n", color,
		get_next_line_counter(GNL_RETURN_COUNT_MODE, 0, NULL, lem),
		message, DEFAULT);
	system("leaks lem-in");
	exit(0);
}

