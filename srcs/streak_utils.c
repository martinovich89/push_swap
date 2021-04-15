/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   streak_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 18:02:07 by mhenry            #+#    #+#             */
/*   Updated: 2021/04/15 18:02:09 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		streak_len(t_list *list, t_elem *start)
{
	int i;

	i = 0;
	list->cur = start;
	while (is_sorted(list->cur, list->cur->next) && i < list->size)
	{
		list->cur = list->cur->next;
		i++;
	}
	list->cur = start;
	while (!is_sorted(list->cur, list->cur->next) && -i < list->size)
	{
		list->cur = list->cur->next;
		i--;
	}
	return (i);
}

int		rev_streak_len(t_list *list, t_elem *start)
{
	int i;

	i = 0;
	list->cur = start;
	while (is_sorted(list->cur->prev, list->cur) && i < list->size)
	{
		list->cur = list->cur->prev;
		i++;
	}
	list->cur = start;
	while (!is_sorted(list->cur->prev, list->cur) && -i < list->size)
	{
		list->cur = list->cur->prev;
		i--;
	}
	return (i);
}

int		set_streak(t_list *list, t_elem *start, int dir)
{
	int i;

	i = 0;
	list->cur = start;
	if (dir == 1)
		i = streak_len(list, start);
	else if (dir == -1)
		i = rev_streak_len(list, start);
	list->streak = i;
	return (i);
}
