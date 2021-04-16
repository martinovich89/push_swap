/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_instructions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 16:45:50 by mhenry            #+#    #+#             */
/*   Updated: 2021/04/15 16:45:55 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_new(t_list *dest)
{
	dest->last = dest->first;
	dest->last->prev = dest->first;
	dest->last->next = dest->first;
	dest->first->prev = dest->first;
	dest->first->next = dest->first;
}

void	push(t_list *dest, t_list *src)
{
	t_elem *tmp;

	tmp = src->first;
	src->last->next = tmp->next;
	tmp->next->prev = src->last;
	src->first = tmp->next;
	if (!dest->size)
		dest->first = tmp;
	tmp->next = dest->first;
	if (dest->first)
		dest->first->prev = tmp;
	if (!dest->size)
		dest->last = dest->first;
	tmp->prev = dest->last;
	if (dest->last)
		dest->last->next = tmp;
	dest->first = tmp;
	src->size--;
	dest->size++;
	if (!dest->size)
		push_new(dest);
}

void	pa(t_env *env)
{
	if (env->b_list->size >= 1)
	{
		push(env->a_list, env->b_list);
		set_list_minmax(env->a_list);
		set_list_minmax(env->b_list);
		if (env->display == 1)
			write(1, "pa\n", 3);
		env->cmd++;
	}
}

void	pb(t_env *env)
{
	if (env->a_list->size >= 1)
	{
		push(env->b_list, env->a_list);
		set_list_minmax(env->a_list);
		set_list_minmax(env->b_list);
		if (env->display == 1)
			write(1, "pb\n", 3);
		env->cmd++;
	}
}
