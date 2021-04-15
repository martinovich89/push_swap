/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 17:59:19 by mhenry            #+#    #+#             */
/*   Updated: 2021/04/15 17:59:21 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		skip_seq(t_env *env, t_list *list, int dir)
{
	int count;

	(void)env;
	count = 0;
	while (is_sorted(list->first, list->first->next))
	{
		if (list->id == 1)
			dir == 1 ? ra(env) : rra(env);
		if (list->id == 2)
			dir == 1 ? rb(env) : rrb(env);
		count++;
	}
	if (!is_sorted(list->first, list->first->next))
	{
		if (list->id == 1)
			dir == 1 ? ra(env) : rra(env);
		if (list->id == 2)
			dir == 1 ? rb(env) : rrb(env);
	}
	return (count);
}

void	choose_roll_dir(t_env *env, t_list *list, int dir)
{
	if (list->id == 1)
		dir < 0 ? rra(env) : ra(env);
	else
		dir < 0 ? rrb(env) : rb(env);
}

void	fix_position(t_env *env, t_list *list, int dir)
{
	int cmp;
	int cmp_sign;

	set_streak(list, list->first, dir);
	cmp = list->streak;
	set_streak(list, list->first, -dir);
	cmp_sign = cmp;
	cmp = (cmp < 0) ? -cmp : cmp;
	if ((cmp_sign > 0 && list->streak > 0) ||
	(cmp_sign < 0 && list->streak < 0))
	{
		while (cmp-- >= 0)
			choose_roll_dir(env, list, dir);
	}
	else
	{
		while (cmp-- > 0 && (list->streak > 1 || list->streak < -1))
			choose_roll_dir(env, list, dir);
	}
}
