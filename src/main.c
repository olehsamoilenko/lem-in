/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 15:31:49 by osamoile          #+#    #+#             */
/*   Updated: 2018/08/24 15:31:50 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	flags_handle(int argc, char **argv, t_lem *lem)
{
	int i = 0;
	while (++i < argc)
	{
		if (ft_strequ(argv[i], "-c"))
			lem->flag_color = 1;
		else if (ft_strequ(argv[i], "-p"))
			lem->flag_pathes = 1;
		else if (ft_strequ(argv[i], "-s"))
			lem->flag_steps = 1;
		else
		{
			ft_putendl("Usage: ./lem-in [-c][-p][-s] < map");
			ft_putendl("\t-c\tcolors");
			ft_putendl("\t-p\tlist of unique pathes");
			ft_putendl("\t-s\ttotal number of steps");
			exit(0);
		}
	}
}

t_lem	*init()
{
	t_lem *lem = ft_memalloc(sizeof(t_lem));
	lem->nodes = NULL;
	lem->start = NULL;
	lem->end = NULL;
	lem->flag_color = 0;
	return (lem);
}

int		main(int argc, char **argv)
{
	t_lem *lem = init();
	flags_handle(argc, argv, lem);
	read_map(lem);
	printf("\n");

	if (lem->start == NULL)
		error("The start room is missing", lem);
	if (lem->end == NULL)
		error("The end room is missing", lem);

	t_list_of_pathes *pathes_1 = NULL;
	t_list_of_pathes *pathes_2 = NULL;

	get_pathes(&pathes_1, &pathes_2, lem);

	if (total_steps(pathes_1, lem) <= total_steps(pathes_2, lem))
		print_steps(pathes_1, lem);
	else
		print_steps(pathes_2, lem);

	system("leaks lem-in");
	return (0);
}
