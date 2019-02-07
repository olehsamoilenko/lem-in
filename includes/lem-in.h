/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 11:39:25 by osamoile          #+#    #+#             */
/*   Updated: 2018/08/02 11:39:26 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

#include "libft.h"

typedef struct	s_node
{
	char					*name;
	struct s_list_of_nodes	*links;
	int						x;
	int						y;
}				t_node;

/*
	name - room's name
	links - array of pointers to linked rooms
	x - coordinate x
	y - coordinate y
*/

typedef struct	s_list_of_nodes
{
	t_node					*node;
	struct s_list_of_nodes	*next;
}				t_list_of_nodes;

/*
	node - pointer to node
	next - pointer to the next element of path
*/

typedef struct	s_list_of_pathes
{
	t_list_of_nodes			*path;
	struct s_list_of_pathes	*next;
}				t_list_of_pathes;

typedef struct	s_lem
{
	int					ants;
	t_list_of_nodes		*nodes;
	t_node				*start;
	t_node				*end;
	t_list_of_pathes	*pathes;
}				t_lem;

/*
	ants - number of ants
	n_nds - number of nodes
	nodes - list of poiners to nodes
	start - pointer to start node
	end - poiner to end node
	n_pts - number of pathes
	pts - array of pointer to pathes
*/

#endif
