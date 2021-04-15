/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cell_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 17:55:15 by mhenry            #+#    #+#             */
/*   Updated: 2021/04/15 17:55:18 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_cell(t_env *env, t_list *dest, t_list *src)
{
	int i;

	(void)dest;
	set_streak(src, src->first, 1);
	src->streak = (src->streak) < 0 ? -src->streak : src->streak;
	i = 0;
	while (i++ <= src->streak)
	{
		if (src->id == 1)
			pb(env);
		else
			pa(env);
	}
}

void	merge_cell_p1(t_env *env, t_list *dest, t_list *src)
{
	while (src->streak >= 0 && dest->streak >= 0)
	{
		if (dest->id == 1)
		{
			if (dest->last->value < src->first->value && src->streak-- >= -1)
				pa(env);
			else
			{
				rra(env);
				dest->streak--;
			}
		}
		else
		{
			if (dest->last->value > src->first->value && src->streak-- >= -1)
				pb(env);
			else
			{
				rrb(env);
				dest->streak--;
			}
		}
	}
}

void	merge_cells(t_env *env, t_list *dest, t_list *src)
{
	set_streak(dest, dest->last, -1);
	set_streak(src, src->first, 1);
	dest->streak = (dest->streak < 0) ? -dest->streak : dest->streak;
	src->streak = (src->streak < 0) ? -src->streak : src->streak;
	merge_cell_p1(env, dest, src);
	while (dest->streak == -1 && src->streak >= 0)
	{
		if (dest->id == 1)
			pa(env);
		else if (dest->id == 2)
			pb(env);
		src->streak--;
	}
	while (dest->streak-- >= 0)
	{
		if (dest->id == 1)
			rra(env);
		else
			rrb(env);
	}
}

void	push_cells(t_env *env, t_list *dest, t_list *src, int nb)
{
	if (dest->size > 0)
	{
		merge_cells(env, dest, src);
		nb--;
	}
	if (src->size > 0)
	{
		while (nb-- > 0)
			push_cell(env, dest, src);
	}
}

int		count_cells(t_list *list)
{
	int		count;
	t_elem	*tmp;

	count = 0;
	list->cur = list->first;
	if (list->size == 0)
		return (0);
	get_next_streak(list);
	tmp = list->cur;
	list->cur = list->cur->next;
	while (list->cur != tmp)
	{
		if (count != 0)
			list->cur = list->cur->next;
		get_next_streak(list);
		count++;
	}
	count = (count == 0) ? 1 : count;
	return (count);
}
