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

# include "libft.h"
#include <stdio.h>

#define MAP_ROOMS_MODE 0
#define MAP_LINKS_MODE 1
#define GNL_READ_MODE 0
#define GNL_RETURN_COUNT_MODE 1

typedef struct	s_node
{
	char					*name;
	struct s_list_of_nodes	*links;
	int						x;
	int						y;
	struct s_node			*bfs_prev;
	int						bfs_used;
	int						bfs_in_queue;
	int						ant_id;
}				t_node;

/*
**	name - room's name
**	links - list of pointers to linked rooms
**	x - coordinate x
**	y - coordinate y

*/

typedef struct	s_list_of_nodes
{
	t_node					*node;
	// int						ants;
	struct s_list_of_nodes	*next;
}				t_list_of_nodes;

/*
	node - pointer to a node
	group - pathes of the same group can be used together
	next - pointer to the next element of the list

*/

typedef struct	s_list_of_pathes
{
	t_list_of_nodes			*path;
	struct s_list_of_pathes	*next;
}				t_list_of_pathes;

/*
	path - pointer to a path
	next - pointer to the next element of the list
*/

typedef struct	s_lem
{
	int						ants;
	t_list_of_nodes			*nodes;
	t_node					*start;
	t_node					*end;
	t_list_of_pathes		*pathes_1;
	t_list_of_pathes		*pathes_2;
}				t_lem;

/*
	ants - number of ants
	nodes - list of pointers to nodes
	start - pointer to the start node
	end - poiner to the end node
	pathes - list of start to end possible ways
*/

typedef struct	s_list_of_ants
{
	int						ant_id;
	t_list_of_nodes			*position;
	struct s_list_of_ants	*next;
}				t_list_of_ants;

// read.c
void	read_map(t_lem *lem);

// main.c

// utils.c
int		get_next_line_counter(int mode, int fd, char **line);
void	error(char *message, t_lem *lem);

// DELETE
void	show_all_nodes(t_list_of_nodes *list, t_lem *lem);

// node
t_node			*create_node(char *line, t_lem *lem);
void			push_node(t_list_of_nodes **list, t_node *node, t_lem *lem);
t_list_of_nodes	*create_list_of_nodes(t_node *first_node);

//link
int		path_contains_node(t_list_of_nodes *path, t_node *node); //rename
void	create_link(char *line, t_lem *lem);


#endif
