/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 15:31:49 by osamoile          #+#    #+#             */
/*   Updated: 2018/08/24 15:31:50 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		total_len(t_list_of_pathes *list)
{
	int len = 0;
	while (list)
	{
		len += path_len(list->path);
		list = list->next;
	}
	return (len);
}

int		list_len(t_list_of_pathes *list)
{
	int res = 0;
	while (list)
	{
		res++;
		list = list->next;
	}
	return (res);
}