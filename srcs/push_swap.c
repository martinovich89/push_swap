/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:01:18 by mhenry            #+#    #+#             */
/*   Updated: 2021/04/16 15:01:20 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void	atob(t_env *env)
{
	int to_push;

	env->a_list->cell_count = count_cells(env->a_list);
	to_push = env->a_list->cell_count / 4;
	to_push = (to_push == 0 && env->a_list->cell_count > 1) ?
	to_push + 1 : to_push;
	push_cells(env, env->b_list, env->a_list, to_push);
	env->a_list->cell_count -= to_push;
	while (env->a_list->cell_count > 1)
	{
		merge_cells(env, env->b_list, env->a_list);
		env->a_list->cell_count--;
	}
}

void	btoa(t_env *env)
{
	int to_push;

	env->b_list->cell_count = count_cells(env->b_list);
	to_push = env->b_list->cell_count / 4;
	to_push = (to_push == 0 && env->b_list->cell_count > 1) ?
	to_push + 1 : to_push;
	push_cells(env, env->a_list, env->b_list, to_push);
	env->b_list->cell_count--;
	while (env->b_list->cell_count > 1)
	{
		merge_cells(env, env->a_list, env->b_list);
		env->b_list->cell_count--;
	}
}

void	make_cells(t_env *env)
{
	env->a_list->dir = 1;
	get_next_streak(env->a_list);
	while (min_streak(env->a_list, env->a_list->cur) < 4 &&
	env->total_numbers > 4)
	{
		env->a_list->start = env->a_list->first;
		env->a_list->cur = env->a_list->start;
		set_streak(env->a_list, env->a_list->first, env->a_list->dir);
		env->a_list->cur = env->a_list->start;
		if (env->a_list->streak >= 4)
			skip_seq(env, env->a_list, 1);
		else if (env->a_list->streak < 4 && env->a_list->streak > -4)
			make_seq(env);
		else if (env->a_list->streak <= -4)
			reverse_seq(env);
		get_next_streak(env->a_list);
	}
}

void	sorting_algorithm(t_env *env)
{
	if (env->total_numbers <= 5)
		sort_small(env);
	fix_position(env, env->a_list, 1);
	env->a_list->start = env->a_list->first;
	env->a_list->cur = env->a_list->start;
	while (!(is_sorted_list(env, env->a_list) == 0 &&
	env->a_list->size == env->total_numbers))
	{
		make_cells(env);
		env->a_list->dir = -1;
		env->b_list->dir = -1;
		if (count_cells(env->a_list) > 1)
			atob(env);
		else if (count_cells(env->b_list) > 1)
			btoa(env);
		else if (count_cells(env->a_list) == 1 &&
		count_cells(env->b_list) == 1)
			btoa(env);
		get_next_streak(env->a_list);
	}
	if (count_cells(env->b_list) > 0)
		btoa(env);
	fix_position(env, env->a_list, 1);
}

int		main(int argc, char **argv)
{
	t_env	*env;

	if (argc == 1)
		return (0);
	if (argc == 2 && argv[1][0] == '\0')
		return (0);
	if (argc == 2 && is_charset_str(argv[1], "- 1234567890") &&
	!is_valid_input_str(argv[1]))
		return (0);
	if (!(env = create_env()))
		ft_error(env, "Error");
	env->display = 1;
	if (parse_args(argc, argv, env) != 0)
		ft_error(env, "Error");
	make_lists(env);
	sorting_algorithm(env);
	destroy_env(env);
	return (0);
}
