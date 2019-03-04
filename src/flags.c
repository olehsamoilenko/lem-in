/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 15:31:49 by osamoile          #+#    #+#             */
/*   Updated: 2018/08/24 15:31:50 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	print_usage()
{
	printf("Usage: ./lem-in [-c][-p][-s] < map\n");
	exit(0);
}

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
			print_usage();
		}
			
	}
}