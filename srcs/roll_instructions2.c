/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roll_instructions2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 16:46:12 by mhenry            #+#    #+#             */
/*   Updated: 2021/04/15 16:46:13 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rra(t_env *env)
{
	if (env->a_list->size >= 2)
	{
		roll(env->a_list, -1);
		write(1, "rra\n", 4);
		env->cmd++;
	}
}

void	rrb(t_env *env)
{
	if (env->b_list->size >= 2)
	{
		roll(env->b_list, -1);
		write(1, "rrb\n", 4);
		env->cmd++;
	}
}

void	rrr(t_env *env)
{
	if (env->a_list->size >= 2)
		roll(env->a_list, -1);
	if (env->b_list->size >= 2)
		roll(env->b_list, -1);
	if (env->a_list->size >= 2 || env->b_list->size >= 2)
		write(1, "rrr\n", 4);
	env->cmd++;
}
