/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_units.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 17:36:35 by mhenry            #+#    #+#             */
/*   Updated: 2021/04/15 17:36:36 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_two(t_env *env, t_list *list)
{
	if (!is_sorted(list->first, list->first->next))
		sa(env);
}

void	sort_three(t_env *env, t_list *list)
{
	if (is_sorted_list(env, list) == 0 &&
	list->first->value != list->min && list->id == 1)
		(list->first->value != list->min &&
		list->first->value != list->max) ? rra(env) : ra(env);
	else if (is_sorted_list(env, list) == 0 &&
	list->first->value != list->min && list->id == 2)
		(list->first->value != list->min &&
		list->first->value != list->max) ? rrb(env) : rb(env);
	else if (!(is_sorted_list(env, list) == 0))
	{
		if (list->first->value == list->min)
		{
			list->id == 1 ? rra(env) : rrb(env);
			list->id == 1 ? sa(env) : sb(env);
		}
		else if (list->first->value == list->max)
		{
			list->id == 1 ? sa(env) : sb(env);
			list->id == 1 ? rra(env) : rrb(env);
		}
		else
			list->id == 1 ? sa(env) : sb(env);
	}
}

void	sort_five(t_env *env, t_list *list)
{
	int count;

	pb(env);
	pb(env);
	if (env->b_list->first->value < env->b_list->last->value)
		sb(env);
	sort_three(env, list);
	count = 3;
	while (count > 0 && env->b_list->size > 0)
	{
		if (list->first->prev->value > env->b_list->first->value)
		{
			rra(env);
			count--;
		}
		else
			pa(env);
	}
	while (count == 0 && env->b_list->size > 0)
		pa(env);
	while (count-- > 0 && env->b_list->size == 0)
		rra(env);
}

void	sort_small(t_env *env)
{
	if (env->a_list->size == 2)
		sort_two(env, env->a_list);
	if (env->a_list->size == 3)
		sort_three(env, env->a_list);
	if (env->a_list->size == 5)
		sort_five(env, env->a_list);
}
