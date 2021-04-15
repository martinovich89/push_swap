/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 23:48:01 by mhenry            #+#    #+#             */
/*   Updated: 2021/04/15 23:48:03 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		is_valid_input(char *line)
{
	size_t i;

	i = 0;
	if (!ft_strcmp(line, "sa") || !ft_strcmp(line, "sb") ||
	!ft_strcmp(line, "ss") || !ft_strcmp(line, "ra") ||
	!ft_strcmp(line, "rb") || !ft_strcmp(line, "rr") ||
	!ft_strcmp(line, "rra") || !ft_strcmp(line, "rrb") ||
	!ft_strcmp(line, "rrr") || !ft_strcmp(line, "pa") ||
	!ft_strcmp(line, "pb"))
		return (1);
	return (0);
}

void	apply_cmd(t_env *env, t_chk *chk)
{
	int i;

	i = 0;
	while (chk->cmd_tab[i])
	{
		pick_cmd(env, chk, i);
		i++;
	}
}

void	make_tab(t_env *env, t_chk *chk)
{
	if (!(chk->cmd_tab = ft_split(chk->cmd_list, ' ')))
		ft_chk_error(env, chk);
}

void	check_sequence(t_env *env)
{
	if (is_sorted_list(env, env->a_list) == 0 &&
	env->a_list->size == env->total_numbers &&
	env->a_list->first->value == env->min)
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
}
