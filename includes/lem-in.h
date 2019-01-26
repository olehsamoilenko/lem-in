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
	char			*name;
	int				n_links;
	struct s_node	*links[100];
	int				x;
	int				y;
}				t_node;

typedef struct	s_path
{
	t_node			*node;
	struct s_path	*next;
}				t_path;

typedef struct	s_lem
{
	int				ants;
	int				n_nds;
	t_node			*nds[100]; //nodes
	t_node			*start;
	t_node			*end;
	int				n_pts;
	t_path			*pts[100]; //pathes
}				t_lem;

#endif
