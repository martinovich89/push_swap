/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_sequence.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 17:38:58 by mhenry            #+#    #+#             */
/*   Updated: 2021/04/15 17:39:02 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	merge_seq_p1(t_env *env, int *count)
{
	while (*count > 0 && env->b_list->size > 0)
	{
		if (env->b_list->first->value < env->a_list->first->value)
		{
			pa(env);
			(*count)++;
		}
		else
		{
			ra(env);
			(*count)--;
		}
	}
}

void	merge_seq_p2(t_env *env, int *count)
{
	while (env->b_list->size > 0)
	{
		if (*count == 1)
		{
			ra(env);
			(*count)--;
		}
		else if (*count == 0)
		{
			pa(env);
			(*count)++;
		}
	}
	while (*count > 0)
	{
		ra(env);
		(*count)--;
	}
}

void	make_seq(t_env *env)
{
	int count;

	pb(env);
	pb(env);
	if (!is_sorted(env->b_list->first, env->b_list->first->next))
		sb(env);
	pb(env);
	if (!is_sorted(env->b_list->first, env->b_list->first->next))
		env->b_list->first->value > env->b_list->last->value ?
		rb(env) : sb(env);
	if (!is_sorted(env->a_list->first, env->a_list->first->next))
		sa(env);
	set_streak(env->a_list, env->a_list->first, 1);
	count = env->a_list->streak + 1;
	merge_seq_p1(env, &count);
	merge_seq_p2(env, &count);
}

void	reverse_seq(t_env *env)
{
	set_streak(env->a_list, env->a_list->first, 1);
	env->a_list->streak = env->a_list->streak < 0 ?
	-env->a_list->streak : env->a_list->streak;
	while (env->a_list->streak >= 2)
	{
		env->a_list->streak--;
		pb(env);
		if (env->b_list->size > 1)
			rb(env);
	}
	sa(env);
	ra(env);
	ra(env);
	env->a_list->streak -= 2;
	while (env->b_list->size > 0)
	{
		pa(env);
		env->a_list->streak++;
	}
	while (env->a_list->streak >= 0)
	{
		ra(env);
		env->a_list->streak--;
	}
}
