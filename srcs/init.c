/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 18:19:26 by mhenry            #+#    #+#             */
/*   Updated: 2021/04/15 18:19:27 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	set_list_minmax(t_list *list)
{
	int i;

	list->cur = list->first;
	list->min = list->cur->value;
	list->max = list->cur->value;
	i = 0;
	while (i < list->size)
	{
		list->cur = list->cur->next;
		if (list->cur->value < list->min)
			list->min = list->cur->value;
		if (list->cur->value > list->max)
			list->max = list->cur->value;
		i++;
	}
}

void	set_elem(t_elem *elem, int nb, t_elem *addr1, t_elem *addr2)
{
	elem->value = nb;
	elem->next = addr1;
	elem->prev = addr2;
}

void	array_to_list(t_env *env, t_list *list)
{
	int i;

	i = 0;
	list->first = create_elem();
	list->cur = list->first;
	list->last = list->cur;
	set_elem(list->cur, env->numbers[i], list->first, list->last);
	list->size++;
	i++;
	while (i < env->total_numbers)
	{
		list->cur->next = create_elem();
		set_elem(list->cur->next, env->numbers[i], list->first, list->cur);
		list->cur = list->cur->next;
		list->last = list->cur;
		list->first->prev = list->last;
		list->size++;
		i++;
	}
}

void	make_lists(t_env *env)
{
	env->a_list = create_list();
	env->a_list->id = 1;
	env->b_list = create_list();
	env->b_list->id = 2;
	array_to_list(env, env->a_list);
	set_list_minmax(env->a_list);
	env->min = env->a_list->min;
	env->max = env->a_list->max;
}
