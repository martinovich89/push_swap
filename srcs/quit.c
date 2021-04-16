/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 18:20:55 by mhenry            #+#    #+#             */
/*   Updated: 2021/04/15 18:20:56 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	destroy_chk(t_chk *chk)
{
	if (chk->cmd_list)
	{
		free(chk->cmd_list);
		chk->cmd_list = NULL;
	}
	if (chk->tmp)
	{
		free(chk->tmp);
		chk->tmp = NULL;
	}
	if (chk->cmd_tab)
	{
		ft_tabdel(chk->cmd_tab);
		chk->cmd_tab = NULL;
	}
}

void	destroy_list(t_list *list)
{
	int i;

	i = 0;
	while (i < list->size)
	{
		list->cur = list->first;
		list->first = list->first->next;
		free(list->cur);
		i++;
	}
	free(list);
}

void	destroy_env(t_env *env)
{
	if (env->a_list)
		destroy_list(env->a_list);
	if (env->b_list)
		destroy_list(env->b_list);
	if (env->numbers)
	{
		free(env->numbers);
		env->numbers = NULL;
	}
	free(env);
}

void	ft_error(t_env *env, char *str)
{
	if (env)
		destroy_env(env);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(1);
}

void	ft_chk_error(t_env *env, t_chk *chk)
{
	destroy_chk(chk);
	ft_error(env, "Error");
}
