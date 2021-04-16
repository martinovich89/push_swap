/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_instructions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 16:44:54 by mhenry            #+#    #+#             */
/*   Updated: 2021/04/15 16:44:55 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap(t_list *list)
{
	int tmp;

	tmp = list->first->value;
	list->first->value = list->first->next->value;
	list->first->next->value = tmp;
}

void	sa(t_env *env)
{
	if (env->a_list->size >= 2)
	{
		swap(env->a_list);
		if (env->display == 1)
			write(1, "sa\n", 3);
		env->cmd++;
	}
}

void	sb(t_env *env)
{
	if (env->b_list->size >= 2)
	{
		swap(env->b_list);
		if (env->display == 1)
			write(1, "sb\n", 3);
		env->cmd++;
	}
}

void	ss(t_env *env)
{
	sa(env);
	sb(env);
	if (env->display == 1)
		write(1, "ss\n", 3);
	env->cmd++;
}
