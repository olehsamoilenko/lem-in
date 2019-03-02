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

int		get_next_line_counter(int mode, int fd, char **line)
{
	static int count = 0;
	if (mode == GNL_READ_MODE)
	{
		count++;
		int res = get_next_line(fd, line);
		if (res)
			printf("%s\n", *line);
		return (res);
	}
	else if (mode == GNL_RETURN_COUNT_MODE)
		return (count);
	else return (0);
}

int		total_steps(t_list_of_pathes *list, t_lem *lem)
{
	int l = total_len(list);
	int k = list_len(list);

	if (k == 0)
		return (__INT_MAX__);

	int res = (lem->ants + l) / k - 1;
	if ((lem->ants + l) % k != 0)
		res += 1;
	return (res);

	// return (-1);
}


void	error(char *message, t_lem *lem)
{
	char *line;

	while (get_next_line(0, &line))
	{
		printf("%s\n", line);
		ft_strdel(&line);

	}
	printf("\n");
	printf("ERROR line %d: %s\n",
		get_next_line_counter(GNL_RETURN_COUNT_MODE, 0, NULL), message);
	system("leaks lem-in");
	exit(0);
}

