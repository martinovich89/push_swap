/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roll_instructions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 16:45:13 by mhenry            #+#    #+#             */
/*   Updated: 2021/04/15 16:45:14 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	roll(t_list *list, int dir)
{
	if (dir > 0)
	{
		list->first = list->first->next;
		list->last = list->last->next;
	}
	else
	{
		list->first = list->first->prev;
		list->last = list->last->prev;
	}
}

void	ra(t_env *env)
{
	if (env->a_list->size >= 2)
	{
		roll(env->a_list, 1);
		if (env->display == 1)
			write(1, "ra\n", 3);
		env->cmd++;
	}
}

void	rb(t_env *env)
{
	if (env->b_list->size >= 2)
	{
		roll(env->b_list, 1);
		if (env->display == 1)
			write(1, "rb\n", 3);
		env->cmd++;
	}
}

void	rr(t_env *env)
{
	if (env->a_list->size >= 2)
		roll(env->a_list, 1);
	if (env->b_list->size >= 2)
		roll(env->b_list, 1);
	if (env->a_list->size >= 2 || env->b_list->size >= 2)
		if (env->display == 1)
			write(1, "rr\n", 3);
	env->cmd++;
}
