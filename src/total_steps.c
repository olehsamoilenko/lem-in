/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   total_steps.c                                      :+:      :+:    :+:   */
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
}
