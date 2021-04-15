/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   streak.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 18:01:54 by mhenry            #+#    #+#             */
/*   Updated: 2021/04/15 18:01:56 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		skip_streak(t_list *list)
{
	int count;

	count = 0;
	while (is_sorted(list->cur, list->cur->next))
	{
		list->cur = list->cur->next;
		count++;
	}
	if (!is_sorted(list->cur, list->cur->next))
		list->cur = list->cur->next;
	return (count);
}

int		min_streak(t_list *list, t_elem *start)
{
	int		ret;
	int		cmp;

	cmp = 0;
	while (list->cur != start || cmp == 0)
	{
		ret = skip_streak(list);
		if (cmp == 0)
			cmp = ret;
		if (ret < 4)
			return (ret);
		cmp = (ret < cmp) ? ret : cmp;
	}
	return (cmp);
}

void	get_next_streak(t_list *list)
{
	t_elem	*tmp;
	int		cmp;
	int		cmp_sign;

	tmp = list->cur;
	cmp = set_streak(list, tmp, 1);
	set_streak(list, tmp, -1);
	cmp_sign = cmp;
	cmp = (cmp < 0) ? -cmp : cmp;
	list->cur = tmp;
	if ((cmp_sign > 0 && list->streak > 0) ||
	(cmp_sign < 0 && list->streak < 0))
	{
		while (cmp-- >= 0)
			list->cur = list->cur->next;
	}
	else
	{
		while (cmp-- > 0 && (list->streak > 1 || list->streak < -1))
			list->cur = list->cur->next;
	}
}
