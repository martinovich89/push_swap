/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 18:15:54 by mhenry            #+#    #+#             */
/*   Updated: 2021/04/15 18:15:55 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_elem	*create_elem(void)
{
	t_elem *elem;

	elem = NULL;
	if (!(elem = malloc(sizeof(t_elem))))
		return (NULL);
	ft_bzero(elem, sizeof(t_elem));
	return (elem);
}

t_list	*create_list(void)
{
	t_list *list;

	list = NULL;
	if (!(list = malloc(sizeof(t_list))))
		return (NULL);
	ft_bzero(list, sizeof(t_list));
	return (list);
}

t_env	*create_env(void)
{
	t_env *env;

	env = NULL;
	if (!(env = malloc(sizeof(t_env))))
		return (NULL);
	ft_bzero(env, sizeof(t_env));
	return (env);
}
