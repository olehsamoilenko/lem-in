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

#ifndef LEMIN_H
# define LEMIN_H

# include "libft.h"

# define MAP_ROOMS_MODE			0
# define MAP_LINKS_MODE			1
# define MAP_ANTS_MODE			2
# define GNL_READ_MODE			0
# define GNL_RETURN_COUNT_MODE	1
# define BFS_ORIGINAL			0
# define BFS_LESS_LINKS			1
# define DEFAULT				"\033[0m"
# define RED					"\033[1;31m"
# define GREEN					"\033[1;32m"
# define YELLOW					"\033[1;33m"
# define BLUE					"\033[1;34m"
# define PURPLE					"\033[1;35m"
# define CYAN					"\033[1;36m"
# define BG_RED					"\033[41m"
# define BG_DEFAULT				"\033[40m"

typedef struct	s_node
{
	char					*name;
	struct s_list_of_nodes	*links;
	int						x;
	int						y;
	struct s_node			*bfs_prev;
	int						bfs_used;
	int						bfs_in_queue;
	int						marked;
}				t_node;

/*
**	name - room's name
**	links - list of pointers to linked rooms
**	x - coordinate x
**	y - coordinate y
**	bfs_prev - previous room for forming path
**	bfs_in_queue - equals 1 if queue contains this node
**	marked - equals 1 if command ##mark modified this node
*/

typedef struct	s_list_of_nodes
{
	t_node					*node;
	struct s_list_of_nodes	*next;
}				t_list_of_nodes;

/*
**	node - pointer to a node
**	next - pointer to the next element of the list
*/

typedef struct	s_list_of_pathes
{
	t_list_of_nodes			*path;
	struct s_list_of_pathes	*next;
}				t_list_of_pathes;

/*
**	path - pointer to a path
**	next - pointer to the next element of the list
*/

typedef struct	s_lem
{
	int						ants;
	t_list_of_nodes			*nodes;
	t_node					*start;
	t_node					*end;
	int						flag_color;
	int						flag_pathes;
	int						flag_steps;
}				t_lem;

/*
**	ants - number of ants
**	nodes - list of pointers to nodes
**	start - pointer to the start node
**	end - poiner to the end node
**	flag_color - equals 1 if -c is enable
**	flag_pathes - equals 1 if -p is enable
**	flag_steps - equals 1 if -s is enable
*/

typedef struct	s_list_of_ants
{
	int						ant_id;
	t_list_of_nodes			*position;
	struct s_list_of_ants	*next;
}				t_list_of_ants;

/*
**	ant_id - number of and for printing
**	position - current position of the ant
**	next - pointer to the next element of the list
*/

void			read_map(t_lem *lem);
void			links_mode(char *line, t_lem *lem);
int				get_next_line_counter(int mode, int fd, char **line,
				t_lem *lem);
void			error(char *message, t_lem *lem);
t_node			*create_node(char *line, t_lem *lem);
int				push_node(t_list_of_nodes **list, t_node *node);
t_list_of_nodes	*create_list_of_nodes(t_node *first_node);
t_node			*pop_node(t_list_of_nodes **list);
void			remove_node(t_list_of_nodes **list, t_node *node);
int				node_in_path(t_list_of_nodes *path, t_node *node);
void			create_link(char *line, t_lem *lem);
int				path_len(t_list_of_nodes *list);
void			delete_path(t_list_of_nodes *path);
void			push_path(t_list_of_pathes **list, t_list_of_nodes *path);
void			ants_contribution(t_list_of_pathes *pathes, t_lem *lem);
void			print_steps(t_list_of_ants *ants, t_lem *lem);
void			print_pathes(t_list_of_pathes *list, t_lem *lem);
void			print_total_steps(int total, t_lem *lem);
void			push_ant(t_list_of_ants **ants, int num,
				t_list_of_nodes *ant_position);
void			remove_ant(t_list_of_ants **ants, t_list_of_ants *ant);
t_list_of_nodes	*bfs(t_lem *lem, int mode);
void			reset_nodes_in_queue(t_list_of_nodes *nodes, t_lem *lem);
void			get_pathes(t_list_of_pathes **pathes_1,
				t_list_of_pathes **pathes_2, t_lem *lem);
void			sort_pathes_by_len(t_list_of_pathes *pathes);
void			sort_nodes_by_amount_of_links(t_list_of_nodes *nodes);
void			rooms_mode(char *line, int *mode, t_lem *lem);

#endif
